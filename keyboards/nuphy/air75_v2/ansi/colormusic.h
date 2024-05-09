#pragma once

#include "user_kb.h"

struct {
    float   smooth              = 0.3;
    float   average_gain        = 1.5;
    float   average_attenuation = 0.01;
    uint8_t rms_left;
    uint8_t rms_right;
    float   average_level;
    float   max_level;
} vu_meter_t;

void  update_vu_meter(uint8_t rms_l, uint8_t rms_r);
float map(float x, float in_min, float in_max, float out_min, float out_max);
