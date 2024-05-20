#pragma once

#include "../colormusic.h"

static void colormusic_complex_init(effect_params_t* params) {
    params->init = true;
}

static bool colormusic_complex_run(effect_params_t* params) {
    if (!is_handshaked()) return true;
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t  l              = vu_l();
    uint8_t  max_active_led = map(l, 0.0f, 255.0f, 0.0f, RGB_MATRIX_LED_COUNT);
    uint16_t time           = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 4);
    int8_t   cos_value      = cos8(time) - 128;
    int8_t   sin_value      = sin8(time) - 128;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        RGB rgb = rgb_matrix_hsv_to_rgb(RAINBOW_BEACON_math(rgb_matrix_config.hsv, cos_value, sin_value, i, time));
        if (i < max_active_led) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool colormusic(effect_params_t* params) {
    if (params->init) colormusic_complex_init(params);
    return colormusic_complex_run(params);
}
