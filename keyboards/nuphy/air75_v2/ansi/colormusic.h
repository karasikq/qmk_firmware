#pragma once

#include "user_kb.h"

typedef struct {
    float smooth;
    float average_gain;
    float average_attenuation;
    float rms_left;
    float rms_right;
    float average_level;
    float max_level;
} vu_meter_t;

void    update_vu_meter(uint8_t rms_l, uint8_t rms_r);
uint8_t vu_l(void);
uint8_t vu_r(void);
float   map(float x, float in_min, float in_max, float out_min, float out_max);
