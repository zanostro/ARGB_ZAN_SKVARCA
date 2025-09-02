#ifndef ADDRESSABLE_RGB_CONTROLLER_H
#define ADDRESSABLE_RGB_CONTROLLER_H

#include "stm32h7xx_hal.h"
#include "leds.h"
#include "animation.h"
#include <stdbool.h>

/* ---- Config for 800 kHz on TIM1 @ 200 MHz ---- */
#define LED_PERIOD_TICKS   299u  // 800 kHz 
#define T1H_TICKS          192u  // ~0.8 µs high
#define T0H_TICKS          96u   // ~0.4 µs high
#define LED_RESET_SLOTS    72u   // >=50 µs low

#define INITIAL_DELAY 	   3000u

#define MAX_ANIMATION_FRAMES 8  // Maximum number of frames an animation can have
#define NUM_LEDS 8  // Number of LEDs in the strip

extern osThreadId_t       LedTaskHandle;

extern osMessageQueueId_t animationQueueHandle;
extern const osThreadAttr_t LedTask_attributes;

extern osMessageQueueId_t LedInitHandle;
extern const osMessageQueueAttr_t LedInit_attributes;



void request_led_stop();

extern Led g_leds[];

void WS2812_RTOS_Init();

uint8_t WS2812_SendOnce(const Led *leds, size_t n);

void WS2812_Test_Blue8_Once();

void WS2812_Test_Rainbow_Once();

void clearFrame();

void LED_Init(void);

void StartLedTask();

uint8_t LED_SendAnimation(Animation* newAnim);

#endif
