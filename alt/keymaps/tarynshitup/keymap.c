#include QMK_KEYBOARD_H

// For STT_CUSTOM_GRADIENT
HSV stt_gradient_0 = {205, 250, 255};
HSV stt_gradient_100 = {140, 215, 125};
bool stt_reflected_gradient = false;
uint8_t stt_gp_i = 0;

typedef struct {
    HSV gradient_0;
    HSV gradient_1;
    bool reflected;
} STT_CUSTOM_PRESETS;



enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    ALT_DEL,               //Added to map left alt + backspace to delete

    STT_G0_HUI,                 //Custom gradient color 1 hue increase
    STT_G0_HUD,                 //Custom gradient color 1 hue decrease
    STT_G0_SAI,                 //Custom gradient color 1 saturation increase
    STT_G0_SAD,                 //Custom gradient color 1 saturation decrease
    STT_G0_VAI,                 //Custom gradient color 1 value increase
    STT_G0_VAD,                 //Custom gradient color 1 value decrease
    STT_G100_HUI,               //Custom gradient color 2 hue increase
    STT_G100_HUD,               //Custom gradient color 2 hue decrease
    STT_G100_SAI,               //Custom gradient color 2 saturation increase
    STT_G100_SAD,               //Custom gradient color 2 saturation decrease
    STT_G100_VAI,               //Custom gradient color 2 value increase
    STT_G100_VAD,               //Custom gradient color 2 value decrease
    STT_GRADIENT_PRESETS,       //Gradient presets
    STT_REFLECTED_GRADIENT,     //Toggle between linear and reflected gradient
    STT_GRADIENT_FLIP,          //Flip the gradient colors

};

// Friendly layer names
enum alt_layers {
    DEF = 0,
    ALT,
    FUNC,
    SUPR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, MO(SUPR),                           KC_SPC,                             KC_RALT, MO(FUNC),KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [ALT] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, KC_LALT,                            _______,                            _______, _______, _______, _______, _______
    ),
    [FUNC] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_MUTE,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_END,
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU,
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, _______, TG(ALT), _______, _______,          KC_PGUP, KC_VOLD,
        _______, _______, KC_LALT,                            _______,                            _______, _______, KC_HOME, KC_PGDN, KC_END
    ),
    [SUPR] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ALT_DEL, _______,
        _______, STT_G0_HUI, STT_G0_HUD, STT_G0_SAI, STT_G0_SAD, STT_G0_VAI, STT_G0_VAD, _______, _______, _______, _______, _______, _______, _______, KC_END,
        _______, STT_G100_HUI, STT_G100_HUD, STT_G100_SAI, STT_G100_SAD, STT_G100_VAI, STT_G100_VAD, _______, _______, _______, _______, _______,          _______, _______,
        _______, STT_GRADIENT_PRESETS, STT_REFLECTED_GRADIENT, STT_GRADIENT_FLIP, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, KC_HOME, _______, KC_END
    )
};


// If the super alt layer is the active layer
bool super_alt_layer_active = false;

// If we need to unregister alt when leaving the super alt layer
bool need_to_unregister_alt = false;

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

// Taken from 'g_led_config' in config_led.c
#define CAPS_LOCK_LED_ID 30

// This runs every matrix scan (every 'frame')
void rgb_matrix_indicators_user(void) {
    led_flags_t flags = rgb_matrix_get_flags();

    // If we're in either keylight or underglow modes (but not both simultaneously)
    if (HAS_FLAGS(flags, LED_FLAG_KEYLIGHT) != HAS_FLAGS(flags, LED_FLAG_UNDERGLOW)) {

        // This fixes a bug where the caps lock LED flickers when toggled in either keylight or underglow modes
        if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
            rgb_matrix_set_color(CAPS_LOCK_LED_ID, RGB_WHITE);
        } else {
            rgb_matrix_set_color(CAPS_LOCK_LED_ID, 0, 0, 0);
        }
    }
}

// This runs code every time that the layers get changed
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case DEF:
            // When returning to the default layer, check if we need to unregister the left alt key
            if (super_alt_layer_active && need_to_unregister_alt) {
                unregister_code(KC_LALT);
            }

            super_alt_layer_active = false;
            need_to_unregister_alt = false;
            break;
        case SUPR:
            super_alt_layer_active = true;
            break;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

uint8_t color_adj_step = 5;
STT_CUSTOM_PRESETS stt_gradient_presets[] = {
    {{205, 250, 255}, {140, 215, 125}, false },
    {{41, 255, 255}, {233, 245, 255}, false },
    {{45, 245, 155}, {160, 255, 80}, false },
    {{173, 245, 40}, {41, 255, 205}, true },
    {{32, 255, 165}, {217, 185, 70}, false },
    {{240, 255, 145}, {115, 255, 245}, true },
    {{118, 255, 255}, {242, 255, 255}, false },
    {{118, 255, 255}, {242, 255, 255}, false },
    {{212, 0, 0}, {223, 235, 165}, true },
};
uint8_t stt_gp_length = sizeof(stt_gradient_presets)/sizeof(stt_gradient_presets[0]);
    static uint32_t key_timer;

    switch (keycode) {

        case STT_G0_HUI:
    if (record->event.pressed) {
        stt_gradient_0.h += color_adj_step;
        dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
    }
    return false;
case STT_G0_HUD:
    if (record->event.pressed) {
        stt_gradient_0.h -= color_adj_step;
        dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
    }
    return false;
case STT_G0_SAI:
    if (record->event.pressed) {
        stt_gradient_0.s = (stt_gradient_0.s + color_adj_step * 2 <= 255) ? stt_gradient_0.s + color_adj_step * 2 : 255;
        dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
    }
    return false;
case STT_G0_SAD:
    if (record->event.pressed) {
        stt_gradient_0.s = (stt_gradient_0.s - color_adj_step * 2 >= 0) ? stt_gradient_0.s - color_adj_step * 2 : 0;
        dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
    }
    return false;
case STT_G0_VAI:
    if (record->event.pressed) {
        stt_gradient_0.v = (stt_gradient_0.v + color_adj_step * 2 <= 255) ? stt_gradient_0.v + color_adj_step * 2 : 255;
        dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
    }
    return false;
case STT_G0_VAD:
    if (record->event.pressed) {
        stt_gradient_0.v = (stt_gradient_0.v - color_adj_step * 2 >= 0) ? stt_gradient_0.v - color_adj_step * 2 : 0;
        dprintf("Gradient 0 HSV: %d, %d, %d\n", stt_gradient_0.h, stt_gradient_0.s, stt_gradient_0.v);
    }
    return false;
case STT_G100_HUI:
    if (record->event.pressed) {
        stt_gradient_100.h += color_adj_step;
        dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
    }
    return false;
case STT_G100_HUD:
    if (record->event.pressed) {
        stt_gradient_100.h -= color_adj_step;
        dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
    }
    return false;
case STT_G100_SAI:
    if (record->event.pressed) {
        stt_gradient_100.s = (stt_gradient_100.s + color_adj_step * 2 <= 255) ? stt_gradient_100.s + color_adj_step * 2 : 255;
        dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
    }
    return false;
case STT_G100_SAD:
    if (record->event.pressed) {
        stt_gradient_100.s = (stt_gradient_100.s - color_adj_step * 2 >= 0) ? stt_gradient_100.s - color_adj_step * 2 : 0;
        dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
    }
    return false;
case STT_G100_VAI:
    if (record->event.pressed) {
        stt_gradient_100.v = (stt_gradient_100.v + color_adj_step * 2 <= 255) ? stt_gradient_100.v + color_adj_step * 2 : 255;
        dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
    }
    return false;
case STT_G100_VAD:
    if (record->event.pressed) {
        stt_gradient_100.v = (stt_gradient_100.v - color_adj_step * 2 >= 0) ? stt_gradient_100.v - color_adj_step * 2 : 0;
        dprintf("Gradient 100 HSV: %d, %d, %d\n", stt_gradient_100.h, stt_gradient_100.s, stt_gradient_100.v);
    }
    return false;
case STT_GRADIENT_PRESETS:
    if (record->event.pressed) {
        stt_gp_i = (stt_gp_i + stt_gp_length ) % stt_gp_length;

        stt_gradient_0 = stt_gradient_presets[stt_gp_i].gradient_0;
        stt_gradient_100 = stt_gradient_presets[stt_gp_i].gradient_1;
        stt_reflected_gradient = stt_gradient_presets[stt_gp_i].reflected;

        stt_gp_i += 1;
    }
    return false;
case STT_REFLECTED_GRADIENT:
    if (record->event.pressed) {
        stt_reflected_gradient = !stt_reflected_gradient;
    }
    return false;
case STT_GRADIENT_FLIP:
    if (record->event.pressed) {
        HSV temp_color = stt_gradient_0;
        stt_gradient_0 = stt_gradient_100;
        stt_gradient_100 = temp_color;
    }
    return false;

        // These are the keys we want to 'fall though' and behave as usual when pressed with the alt modifier
        case KC_A ... KC_Z:
        case KC_TAB:
        case KC_DEL:
        case KC_UP:
        case KC_DOWN:
        case MO(FUNC):
            if (super_alt_layer_active && record->event.pressed) {
                // Only activate the alt modifier for the first key press
                if ((get_mods() & MOD_BIT(KC_LALT)) == false) {
                    register_code(KC_LALT);
                    need_to_unregister_alt = true;
                }
            }
            // We still want to process the keycode normally
            return true;
        case ALT_DEL:
            if (record->event.pressed) {
                register_code(KC_DEL);
            } else {
                unregister_code(KC_DEL);
            }
            return false;
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}



void matrix_init_user(void) {
   rgb_matrix_enable();
   rgb_matrix_sethsv(100, 220, 220);
   rgb_matrix_mode (RGB_MATRIX_RAINDROPS);

};

