#include "animation.h"
#include <math.h>



uint32_t FrameDelayTicks(uint32_t fps)
{
    if (fps == 0) fps = 1;
    uint32_t num = (uint32_t)configTICK_RATE_HZ + (fps / 2);
    uint32_t ticks = (uint32_t)(num / fps);
    if (ticks < 1) ticks = 1;
    return ticks;

}

uint16_t FillRainbow(Led *leds, size_t n, uint16_t startHue)
{
    if (n == 0) return -1;
    uint16_t endHue = 0;
    uint16_t hueStep = 360 / n;

    for (size_t i = 0; i < n; ++i) {
        uint16_t hue = (startHue + i * hueStep) % 360;
        leds[i] = hue_to_rgb(hue);
        endHue = hue;
    }
    return endHue;
}

// rainbow
Animation* TestAnimation1(){
	uint32_t led_count = LED_COUNT;
	uint32_t fps  = 5;
	if (led_count == 0) return NULL;

	const uint32_t frame_count = 8u;
	const size_t pixels = (size_t)frame_count * (size_t)led_count;

	Led *buff = (Led*)pvPortMalloc(pixels * sizeof(Led));
	if (!buff) return NULL;
	uint16_t hue = 0;

	for(int i = 0; i < frame_count; i++){
		Led *fr = &buff[i * led_count];
		hue = FillRainbow(fr, LED_COUNT, hue);

	}

	Animation *a = Animation_Create(fps, led_count, frame_count,/*loop=*/1u, buff, 1u);

	if (!a) { vPortFree(buff); return NULL; }
	return a;
}

// Police Light Pattern
Animation* TestAnimation2()
{
	uint32_t led_count = LED_COUNT;
	uint32_t fps  = 20;  
    if (led_count == 0) return NULL;

    const uint32_t frame_count = 8u;  
    const size_t pixels = (size_t)frame_count * (size_t)led_count;

    Led *buf = (Led*)pvPortMalloc(pixels * sizeof(Led));
    if (!buf) return NULL;

    Led *f0 = &buf[0 * led_count];  
    Led *f1 = &buf[1 * led_count];  
    Led *f2 = &buf[2 * led_count];  
    Led *f3 = &buf[3 * led_count];
    Led *f4 = &buf[4 * led_count];
    Led *f5 = &buf[5 * led_count];
    Led *f6 = &buf[6 * led_count];
    Led *f7 = &buf[7 * led_count];
    
    uint32_t half = led_count / 2;
    
    for (uint32_t i = 0; i < led_count; ++i) {
        f0[i] = (i < half) ? (Led){ .r = 255, .g = 0, .b = 0 } : (Led){ .r = 0, .g = 0, .b = 0 };
        f1[i] = (i < half) ? (Led){ .r = 255, .g = 0, .b = 0 } : (Led){ .r = 0, .g = 0, .b = 0 };
        f2[i] = (Led){ .r = 0, .g = 0, .b = 0 };
        f3[i] = (i >= half) ? (Led){ .r = 0, .g = 0, .b = 255 } : (Led){ .r = 0, .g = 0, .b = 0 };
        f4[i] = (i >= half) ? (Led){ .r = 0, .g = 0, .b = 255 } : (Led){ .r = 0, .g = 0, .b = 0 };
        f5[i] = (Led){ .r = 0, .g = 0, .b = 0 };
        f6[i] = (i % 2 == 0) ? (Led){ .r = 255, .g = 0, .b = 0 } : (Led){ .r = 0, .g = 0, .b = 255 };
        f7[i] = (i % 2 == 0) ? (Led){ .r = 0, .g = 0, .b = 255 } : (Led){ .r = 255, .g = 0, .b = 0 };
    }

    Animation *a = Animation_Create(fps, led_count, frame_count,/*loop=*/1u, buf, 1u);

    if (!a) { vPortFree(buf); return NULL; }
    return a;
}



// Blue and Purple Pulsing from Center
Animation* TestAnimation3(){
	uint32_t led_count = LED_COUNT;
	uint32_t fps  = 4; 

	const uint32_t frame_count = 12u; 
	const size_t pixels = (size_t)frame_count * (size_t)led_count;

	Led *buff = (Led*)pvPortMalloc(pixels * sizeof(Led));
	if (!buff) return NULL;

	uint32_t center = led_count / 2;
	uint32_t max_distance = (led_count + 1) / 2;  
	
	for(uint32_t frame = 0; frame < frame_count; frame++){
		Led *current_frame = &buff[frame * led_count];
		
		float formation_progress = (float)frame / (float)(frame_count - 1);
		float formation_intensity = formation_progress * formation_progress;
		
		for(uint32_t i = 0; i < led_count; i++){
			uint32_t distance = (i < center) ? (center - i) : (i - center);
			
			float wave_position = formation_progress * (float)max_distance;
			float distance_from_wave = fabs((float)distance - wave_position);
			
			float pulse_intensity = 0.0f;
			if(distance_from_wave < 2.0f) {
				pulse_intensity = (2.0f - distance_from_wave) / 2.0f;  
			}
			
			float edge_fadeout = 1.0f - ((float)distance / (float)max_distance);
			edge_fadeout = edge_fadeout * edge_fadeout;  
			
			float final_intensity = pulse_intensity * edge_fadeout * formation_intensity;
			
			float purple_mix = (float)distance / (float)max_distance;
			if(purple_mix > 1.0f) purple_mix = 1.0f;
			
			uint8_t red = (uint8_t)(128 * purple_mix * final_intensity);
			uint8_t green = 0;
			uint8_t blue = (uint8_t)(255 * final_intensity);
			
			current_frame[i] = (Led){.r = red, .g = green, .b = blue};
		}
	}
	
	Animation *a = Animation_Create(fps, led_count, frame_count,/*loop=*/1u, buff, 1u);
	if (!a) { vPortFree(buff); return NULL; }
	return a;
}


