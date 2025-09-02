#ifndef ANIMATION_H
#define ANIMATION_H

#include "leds.h"



typedef struct {
    uint32_t fps;
    uint32_t led_count;     // LEDs per frame
    uint32_t frame_count;   // number of frames
    uint8_t  loop;          // 0/1
    uint8_t  owns_frames;   // 1 = destructor will free frames
    Led     *frames;        // flat buffer: frame_count * led_count
} Animation;


static inline Animation* Animation_Create(uint32_t fps,
                                          uint32_t led_count,
                                          uint32_t frame_count,
                                          uint8_t  loop,
                                          Led *frames_flat,
                                          uint8_t take_ownership)
{
    Animation *a = (Animation*)pvPortMalloc(sizeof(Animation));
    if (!a) return NULL;
    a->fps         = fps;
    a->led_count   = led_count;
    a->frame_count = frame_count;
    a->loop        = loop;
    a->frames      = frames_flat;
    a->owns_frames = take_ownership ? 1u : 0u;
    return a;
}


static inline void Animation_Destroy(Animation *a)
{
    if (!a) return;
    if (a->frames) {
        vPortFree(a->frames);
    }
    vPortFree(a);
}

/* Get pointer to the first LED of frame 'idx'. */
static inline Led* Animation_GetFrame(Animation *a, uint32_t idx)
{
    if (!a || idx >= a->frame_count) return NULL;
    return &a->frames[idx * a->led_count];
}

// Convert frames to delay ticks
uint32_t FrameDelayTicks(uint32_t fps);

// 3 static colors
Animation* TestAnimation1();

// rainbow
Animation* TestAnimation2();

// single color
Animation* TestAnimation3();

#endif
