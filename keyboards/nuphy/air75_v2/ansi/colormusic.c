#include "colormusic.h"
#include "print.h"

vu_meter_t vu_meter = {.smooth = 0.3f, .average_gain = 1.5f, .average_attenuation = 0.01f, .rms_left = 0.0f, .rms_right = 0.0f, .average_level = 0.5f, .max_level = 1.0f};

bool via_command_kb(uint8_t *data, uint8_t length) {
    if (data[0] != 'k' || data[1] != 'b' || data[2] != 'm') return 1;
    update_vu_meter(data[3], data[4]);
    return 0;
}

void update_vu_meter(uint8_t input_l, uint8_t input_r) {
    float l                = ((float)input_l) / 255.0f;
    float r                = ((float)input_r) / 255.0f;
    vu_meter.rms_left      = l * vu_meter.smooth - vu_meter.rms_left * (1.0f - vu_meter.smooth);
    vu_meter.rms_right     = r * vu_meter.smooth - vu_meter.rms_right * (1.0f - vu_meter.smooth);
    float average          = (vu_meter.rms_left + vu_meter.rms_right) / 2.0f;
    vu_meter.average_level = average * vu_meter.average_attenuation + vu_meter.average_level * vu_meter.average_gain;
    vu_meter.max_level     = vu_meter.average_level * vu_meter.average_gain;

    dprintf("RMS: %2u;%2u", vu_l(), vu_r());
}

float map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint8_t vu_l(void) {
    return map(vu_meter.rms_left, 0.0f, vu_meter.max_level, 0.0f, 255.0f);
}
uint8_t vu_r(void) {
    return map(vu_meter.rms_right, 0.0f, vu_meter.max_level, 0.0f, 255.0f);
}
