RGB_MATRIX_EFFECT(my_cool_effect2)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "colormusic.h"

static HSV color;
static void my_cool_effect2_complex_init(effect_params_t* params) {
}
static bool my_cool_effect2_complex_run(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

  for (uint8_t i = led_min; i < led_max; i++) {
      color.h += 1;
    rgb_matrix_set_color(i, 0xff, rms_left, 0xff);
  }

  return true;
}
static bool my_cool_effect2(effect_params_t* params) {
  if (params->init) my_cool_effect2_complex_init(params);
  return my_cool_effect2_complex_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
