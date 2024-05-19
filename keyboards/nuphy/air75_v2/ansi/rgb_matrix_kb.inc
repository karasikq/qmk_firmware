RGB_MATRIX_EFFECT(colormusic)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "colormusic.h"

static void colormusic_complex_init(effect_params_t* params) {
    params->init = true;
}

static bool colormusic_complex_run(effect_params_t* params) {
    if (!is_handshaked()) return true;
    // RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t l = vu_l();
    uint8_t mapped = map(l, 0.0f, 255.0f, 0.0f, RGB_MATRIX_LED_COUNT);
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        // RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = {.h = 128 - map(i, 0.0f, RGB_MATRIX_LED_COUNT, 0.0f, 128.0f), .s = 255, .v = 128};
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        if (i <= mapped) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }
    return rgb_matrix_check_finished_leds(RGB_MATRIX_LED_COUNT);
}

static bool colormusic(effect_params_t* params) {
  if (params->init) colormusic_complex_init(params);
  return colormusic_complex_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
