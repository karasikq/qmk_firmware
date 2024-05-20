#include "colormusic.h"
#include "print.h"
#include "raw_hid.h"

vu_meter_t vu_meter = {.smooth = 0.5f, .average_gain = 1.6f, .average_attenuation = 0.01f, .rms_left = 0.0f, .rms_right = 0.0f, .average_level = 0.5f, .max_level = 1.0f};

handshake_t handshake = {.status = 0, .last_value = 0};

bool via_command_kb(uint8_t *data, uint8_t length) {
    if (data[0] != 'k' || data[1] != 'b' || data[2] != 'm') return 0;
    if (data[3] == 0x01) {
        if (handshake.status == 0) {
            uint8_t response[length];
            memset(response, 0, length);
            handshake.last_value = data[4] + 1;
            response[0]          = 'k';
            response[1]          = 'b';
            response[2]          = 'm';
            response[3]          = 0x01;
            response[4]          = handshake.last_value;
            raw_hid_send(response, length);
            handshake.status = 1;
            return 1;
        }
        if (handshake.status == 1 && handshake.last_value + 1 == data[4]) {
            handshake.status = 2;
            return 1;
        } else {
            handshake.status = 0;
            return via_command_kb(data, length);
        }
    }
    if (data[3] != 0x02) return 1;
    update_vu_meter(data[4], data[5]);
    return 1;
}

void update_vu_meter(uint8_t input_l, uint8_t input_r) {
    float l                = ((float)input_l) / 255.0f;
    float r                = ((float)input_r) / 255.0f;
    vu_meter.rms_left      = l * vu_meter.smooth - vu_meter.rms_left * (1.0f - vu_meter.smooth);
    vu_meter.rms_right     = r * vu_meter.smooth - vu_meter.rms_right * (1.0f - vu_meter.smooth);
    float average          = (vu_meter.rms_left + vu_meter.rms_right) / 2.0f;
    vu_meter.average_level = average * vu_meter.average_attenuation + vu_meter.average_level * (1.0f - vu_meter.average_attenuation);
    vu_meter.max_level     = vu_meter.average_level * vu_meter.average_gain;

    dprintf("RMS: %2u;%2u\n", vu_l(), vu_r());
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

uint8_t is_handshaked(void) {
    return handshake.status == 2;
}
