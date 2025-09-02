#ifndef LEDS_H
#define LEDS_H

#define LED_COUNT 8u

#include "cmsis_os.h"

typedef struct {
    uint8_t r, g, b;
} Led;

Led hue_to_rgb(uint16_t hue);

#endif
