#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _MEDIA,
    _NAV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    KC_ENT, KC_1, KC_2,
    KC_3,   KC_4, KC_5,
    KC_6,   KC_7, KC_8
),

[_MEDIA] = LAYOUT(
    KC_MPLY, KC_VOLU, KC_MUTE,
    KC_MPRV, KC_VOLD, KC_MNXT,
    RGB_TOG, RGB_MOD, QK_BOOT
),

[_NAV] = LAYOUT(
    KC_ESC,  KC_UP,   KC_TAB,
    KC_LEFT, KC_DOWN, KC_RGHT,
    KC_HOME, KC_END,  KC_DEL
)

};

bool encoder_update_user(uint8_t index, bool clockwise) {

    if (clockwise) {

        if (get_highest_layer(layer_state) == _BASE) {
            layer_move(_MEDIA);
        }
        else if (get_highest_layer(layer_state) == _MEDIA) {
            layer_move(_NAV);
        }
        else {
            layer_move(_BASE);
        }

    } else {

        if (get_highest_layer(layer_state) == _BASE) {
            layer_move(_NAV);
        }
        else if (get_highest_layer(layer_state) == _MEDIA) {
            layer_move(_BASE);
        }
        else {
            layer_move(_MEDIA);
        }
    }

    return false;
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {

    oled_clear();

    oled_set_cursor(0,0);
    oled_write_ln_P(PSTR("PixelPlay"), false);

    oled_set_cursor(0,2);

    switch (get_highest_layer(layer_state)) {

        case _BASE:
            oled_write_ln_P(PSTR("Layer: BASE"), false);
            break;

        case _MEDIA:
            oled_write_ln_P(PSTR("Layer: MEDIA"), false);
            break;

        case _NAV:
            oled_write_ln_P(PSTR("Layer: NAV"), false);
            break;

        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    return false;
}

#endif
