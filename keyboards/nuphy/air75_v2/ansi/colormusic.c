#include "colormusic.h"

bool via_command_kb(uint8_t *data, uint8_t length) {
    if (data[0] != 'k' || data[1] != 'b' || data[2] != 'm') return true;
    rms_left  = data[3];
    rms_right = data[4];

    return false;
}

void update_vu_meter(uint8_t rms_l, uint8_t rms_r) {
    float l                  = (float)rms_l / 255.0;
    float r                  = (float)rms_r / 255.0;
    vu_meter_t.rms_left      = l * vu_meter_t.smooth - vu_meter_t.rms_left * (1.0 - vu_meter_t.smooth);
    vu_meter_t.rms_right     = r * vu_meter_t.smooth - vu_meter_t.rms_right * (1.0 - vu_meter_t.smooth);
    float average            = (vu_meter_t.rms_left + vu_meter_t.rms_right) / 2.0;
    vu_meter_t.average_level = average * vu_meter_t.average_attenuation + vu_meter_t.average_level * vu_meter_t.average_gain;
    vu_meter_t.max_level     = vu_meter_t.average_level * vu_meter_t.average_gain;
}

float map(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
