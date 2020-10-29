// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(my_cool_effect)
RGB_MATRIX_EFFECT(my_cool_effect2)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool my_cool_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0xff, 0xff, 0x00);
  }
  return led_max < DRIVER_LED_TOTAL;
}

// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
static uint8_t some_global_state;
static void my_cool_effect2_complex_init(effect_params_t* params) {
  some_global_state = 1;
}
static bool my_cool_effect2_complex_run(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0xff, some_global_state++, 0xff);
  }

  return led_max < DRIVER_LED_TOTAL;
}
static bool my_cool_effect2(effect_params_t* params) {
  if (params->init) my_cool_effect2_complex_init(params);
  return my_cool_effect2_complex_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS




#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#    ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
RGB_MATRIX_EFFECT(SOLID_REACTIVE_SIMPLE)
#        ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV SOLID_REACTIVE_SIMPLE_math(HSV hsv, uint16_t offset) {
    hsv.v = scale8(255 - offset, hsv.v);
    return hsv;
}

bool SOLID_REACTIVE_SIMPLE(effect_params_t* params) { return effect_runner_reactive(params, &SOLID_REACTIVE_SIMPLE_math); }

#        endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#    endif      // DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#endif          // RGB_MATRIX_KEYREACTIVE_ENABLED



/*   Custom gradient that can be tweaked by keycodes
...........................................................*/
RGB_MATRIX_EFFECT(STT_CUSTOM_GRADIENT)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "effects/stt_custom_gradient.c"
#endif

/*   Wide Rainbow Cycle Left to Right
...........................................................*/
RGB_MATRIX_EFFECT(STT_WIDE_RAINBOW_GRADIENT)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "effects/stt_wide_rainbow_gradient.c"
#endif
