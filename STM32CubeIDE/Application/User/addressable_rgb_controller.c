#include "addressable_rgb_controller.h"
#include "main.h"
#include "stm32h7xx_hal_tim.h"
#include <stdbool.h>
#include <string.h>

#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"


static SemaphoreHandle_t wsDoneSem;


extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch1;

osThreadId_t LedTaskHandle;
const osThreadAttr_t LedTask_attributes = {
  .name = "LedTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

osMessageQueueId_t animationQueueHandle;
const osMessageQueueAttr_t animationQueue_attributes = {
		.name = "SendAnimation"
};

osMessageQueueId_t LedInitHandle;
const osMessageQueueAttr_t LedInit_attributes = {
		.name = "SendAnimation"
};



// DMA buffer
__attribute__((section(".RAM_D2"), aligned(32)))
static uint16_t s_ticks_buf[LED_COUNT*24u + LED_RESET_SLOTS];


Led g_leds[LED_COUNT];
static volatile bool s_dma_done = false;

void LED_Init(void){
  animationQueueHandle = osMessageQueueNew(5, sizeof(Animation*), &animationQueue_attributes);
  LedInitHandle = osMessageQueueNew(1, sizeof(uint8_t), &LedInit_attributes);
}


static inline uint16_t bit_to_ticks(uint8_t bit) { return bit ? T1H_TICKS : T0H_TICKS; }


// Build CCR values from RGB array (WS2812 = GRB on the wire)
static size_t build_ticks(const Led *leds, size_t n, uint16_t *out)
{
    // Fill buffer with bit timings
    size_t w = 0;
    for (size_t i = 0; i < n; ++i) {
        const uint8_t bytes[3] = { leds[i].g, leds[i].r, leds[i].b };
        for (int bi = 0; bi < 3; ++bi) {
            uint8_t v = bytes[bi];
            for (int b = 7; b >= 0; --b)
                out[w++] = bit_to_ticks((v >> b) & 1u);
        }
    }
    for (size_t i = 0; i < LED_RESET_SLOTS; ++i) out[w++] = 0u; // reset sequence
    return w;
}

uint8_t WS2812_SendOnce(const Led *leds, size_t n)
{
    const size_t need = n*24u + LED_RESET_SLOTS;
    if (need > (sizeof(s_ticks_buf)/sizeof(s_ticks_buf[0]))) return false;

    size_t wrote = build_ticks(leds, n, s_ticks_buf);

    // make sure DMA sees fresh data
    SCB_CleanDCache_by_Addr((uint32_t*)s_ticks_buf, wrote * sizeof(uint16_t));

    if (wsDoneSem) xSemaphoreTake(wsDoneSem, 0);
    if (HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t*)s_ticks_buf, wrote) != HAL_OK)
        return false;

    if (xSemaphoreTake(wsDoneSem, portMAX_DELAY) != pdTRUE)
    	return false;

    return true;
}

// HAL callback from the DMA IRQ -> stop after full buffer
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1) {
        HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
        BaseType_t hpw = pdFALSE;
        xSemaphoreGiveFromISR(wsDoneSem, &hpw);
        portYIELD_FROM_ISR(hpw);
    }
}

void HAL_TIM_PWM_ErrorCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1) {
        BaseType_t hpw = pdFALSE;
        xSemaphoreGiveFromISR(wsDoneSem, &hpw);
        portYIELD_FROM_ISR(hpw);
    }
}


void WS2812_Test_Blue8_Once()
{
    for (size_t i = 0; i < LED_COUNT; ++i) {
        g_leds[i].r = 0x00;
        g_leds[i].g = 0x00;
        g_leds[i].b = 0xFF;
    }
    (void)WS2812_SendOnce(g_leds, LED_COUNT);
}



void WS2812_Test_Rainbow_Once()
{
    WS2812_FillRainbow(g_leds, LED_COUNT, 0);
    WS2812_SendOnce(g_leds, LED_COUNT);
}


void clearFrame(){
	for (size_t i = 0; i < LED_COUNT; ++i) {
	        g_leds[i].r = 0x00;
	        g_leds[i].g = 0x00;
	        g_leds[i].b = 0x00;
	    }
	WS2812_SendOnce(g_leds, LED_COUNT);
}

//send new animation to the LED task
uint8_t LED_SendAnimation(Animation* newAnim) {
    if (!newAnim) return 0;
    osStatus status = osMessageQueuePut(animationQueueHandle, &newAnim, 0, 0);
    return (status == osOK) ? 1 : 0;
}

void WS2812_RTOS_Init()
{
    wsDoneSem = xSemaphoreCreateBinary();
}







