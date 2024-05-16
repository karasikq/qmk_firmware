RGB_MATRIX_EFFECT(colormusic)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "colormusic.h"

static void colormusic_complex_init(effect_params_t* params) {
    params->init = true;
}

static bool colormusic_complex_run(effect_params_t* params) {
  rgb_matrix_set_color_all(0, 0, vu_l());
  return true;
}

static bool colormusic(effect_params_t* params) {
  if (params->init) colormusic_complex_init(params);
  return colormusic_complex_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
