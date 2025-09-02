#include "leds.h"


// Convert hue [0..359] to RGB
Led hue_to_rgb(uint16_t hue)
{
    Led c = {0};
    uint8_t region = hue / 60;
    uint8_t remainder = (hue % 60) * 255 / 60;
    uint8_t p = 0;
    uint8_t q = 255 - remainder;
    uint8_t t = remainder;

    switch (region) {
    default:
    case 0: c.r = 255; c.g = t;   c.b = 0;   break;
    case 1: c.r = q;   c.g = 255; c.b = 0;   break;
    case 2: c.r = 0;   c.g = 255; c.b = t;   break;
    case 3: c.r = 0;   c.g = q;   c.b = 255; break;
    case 4: c.r = t;   c.g = 0;   c.b = 255; break;
    case 5: c.r = 255; c.g = 0;   c.b = q;   break;
    }
    return c;
}


