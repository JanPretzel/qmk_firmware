#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

extern rgblight_config_t rgblight_config;

// Aliases
#define ____ KC_TRNS
#define _    KC_NO

// Layers
enum {
  QWERTY = 0,
  SYMB,
  MDIA,
  NAV,
  GAME,
};

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  COPY,
  PASTE,
  CUT,
};

/* OS Identifier */
enum {
  OS_WIN = 0,
  OS_LIN,
};

uint8_t os_type = OS_LIN;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Qwerty layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  | Lead |           | SYMB |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | GUI    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | SHIFT  |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | CTRL |      |      | Left | Right|                                       |  Up  | Down |      |       | F12 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | ALT  | GAME |       | Alt  | Ctrl   |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 | /SYMB|ace   |      |       | PgDn |        | /SYMB|
 *                                 `--------------------'       `----------------------'
 */
[QWERTY] = LAYOUT_ergodox(
      // left hand
      KC_ESC,         KC_1,         KC_2,   KC_3,     KC_4,             KC_5,           _,
      KC_TAB,         KC_Q,         KC_W,   KC_E,     KC_R,             KC_T,           KC_LEAD,
      KC_LGUI,        KC_A,         KC_S,   KC_D,     LT(NAV, KC_F),    KC_G,
      KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,     KC_V,             KC_B,           ALL_T(KC_NO),
      KC_LCTL,        _,            _,      KC_LEFT,  KC_RGHT,
                                                                        KC_LALT,  TG(GAME),
                                                                                        _,
                                                      LT(SYMB, KC_SPC), KC_BSPC,        _,
      // right hand
      _,              KC_6, KC_7,   KC_8,     KC_9,   KC_0,               KC_MINS,
      TG(SYMB),       KC_Y, KC_U,   KC_I,     KC_O,   KC_P,               KC_BSLS,
                      KC_H, KC_J,   KC_K,     KC_L,   LT(MDIA, KC_SCLN),  GUI_T(KC_QUOT),
      MEH_T(KC_NO),   KC_N, KC_M,   KC_COMM,  KC_DOT, CTL_T(KC_SLSH),     KC_RSFT,
                            KC_UP,  KC_DOWN,  _,      _,                  KC_F12,
      KC_LALT,  KC_RCTL,
      KC_PGUP,
      KC_PGDN,KC_TAB, LT(SYMB, KC_ENT)
),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = LAYOUT_ergodox(
      // left hand
      ____, KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    ____,
      ____, KC_EXLM,  KC_AT,    KC_LCBR,  KC_RCBR,  KC_PIPE,  ____,
      ____, KC_HASH,  KC_DLR,   KC_LPRN,  KC_RPRN,  KC_GRV,
      ____, KC_PERC,  KC_CIRC,  KC_LBRC,  KC_RBRC,  KC_TILD,  ____,
      ____, ____,     ____,     ____,     ____,
                                                    ____,     ____,
                                                    ____,
                                          ____,     ____,     ____,
      // right hand
      ____,   KC_F6,    KC_F7,  KC_F8,    KC_F9,    KC_F10,   KC_F11,
      ____,   KC_UP,    KC_7,   KC_8,     KC_9,     KC_ASTR,  KC_F12,
              KC_DOWN,  KC_4,   KC_5,     KC_6,     KC_PLUS,  ____,
      ____,   KC_AMPR,  KC_1,   KC_2,     KC_3,     KC_BSLS,  ____,
                        ____,   KC_DOT,   KC_0,     KC_EQL,   ____,
      ____,   ____,
      ____,
      ____,   ____,     ____
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Play   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | VolUp  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | VolDn  |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Mute   |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Prev | Next |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[MDIA] = LAYOUT_ergodox(
      // left hand
      KC_MPLY, ____,     ____, ____, ____, ____, ____,
      KC_VOLU, ____,     ____, ____, ____, ____, ____,
      KC_VOLD, ____,     ____, ____, ____, ____,
      KC_MUTE, ____,     ____, ____, ____, ____, ____,
      KC_MPRV, KC_MNXT,  ____, ____, ____,
                                           ____, ____,
                                                 ____,
                                     ____, ____, ____,
      // right hand
      ____,  ____, ____, ____, ____, ____, ____,
      ____,  ____, ____, ____, ____, ____, ____,
             ____, ____, ____, ____, ____, ____,
      ____,  ____, ____, ____, ____, ____, ____,
                   ____, ____, ____, ____, ____,
      ____, ____,
      ____,
      ____, ____, ____
),
/* Keymap 3: Navigation Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | Home | Up   | End  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      | Left | Down | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | Copy | Paste| Cut  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      | ALT  |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NAV] = LAYOUT_ergodox(
      // left hand
      ____, ____, ____, ____, ____, ____, ____,
      ____, ____, ____, ____, ____, ____, ____,
      ____, ____, ____, ____, ____, ____,
      ____, ____, ____, ____, ____, ____, ____,
      ____, ____, ____, ____, KC_LALT,
                                    ____, ____,
                                          ____,
                              ____, ____, ____,
      // right hand
      ____, ____, ____,       ____,       ____,       ____, ____,
      ____, ____, KC_HOME,    KC_UP,      KC_END,     ____, ____,
            ____, KC_LEFT,    KC_DOWN,    KC_RIGHT,   ____, ____,
      ____, ____, COPY,       PASTE,      CUT,        ____, ____,
                  ____,       ____,       ____,       ____, ____,
      ____, ____,
      ____,
      ____, ____, ____
),
/* Keymap 4: Gaming
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | XXXX   |      |      |      | F    |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | CTRL |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Space|      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 *
 * The gaming layer turns of some layer switches, the windows key and some one shot keys.
 */
[GAME] = LAYOUT_ergodox(
      // left hand
      ____,     ____, ____, ____, ____,   ____, ____,
      ____,     ____, ____, ____, ____,   ____, ____,
      _,        ____, ____, ____, KC_F,   ____,
      ____,     ____, ____, ____, ____,   ____, ____,
      KC_LCTL,  ____, ____, ____, ____,
                                          ____, ____,
                                                ____,
                                  KC_SPC, ____, ____,
      // right hand
      ____,  ____, ____, ____, ____, ____, ____,
      ____,  ____, ____, ____, ____, ____, ____,
             ____, ____, ____, ____, ____, ____,
      ____,  ____, ____, ____, ____, ____, ____,
                   ____, ____, ____, ____, ____,
      ____, ____,
      ____,
      ____, ____, ____
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;

    case COPY:
      if (record->event.pressed) {
        switch (os_type) {
          case OS_WIN:
            register_code(KC_LCTL);
            tap_code(KC_C);
            unregister_code(KC_LCTL);
            break;
          case OS_LIN:
            register_code(KC_LGUI);
            tap_code(KC_C);
            unregister_code(KC_LGUI);
            break;
        }
      }
      return false;
      break;

    case PASTE:
      if (record->event.pressed) {
        switch (os_type) {
          case OS_WIN:
            register_code(KC_LCTL);
            tap_code(KC_V);
            unregister_code(KC_LCTL);
            break;
          case OS_LIN:
            register_code(KC_LGUI);
            tap_code(KC_V);
            unregister_code(KC_LGUI);
            break;
        }
      }
      return false;
      break;

    case CUT:
      if (record->event.pressed) {
        switch (os_type) {
          case OS_WIN:
            register_code(KC_LCTL);
            tap_code(KC_X);
            unregister_code(KC_LCTL);
            break;
          case OS_LIN:
            register_code(KC_LGUI);
            tap_code(KC_X);
            unregister_code(KC_LGUI);
            break;
        }
      }
      return false;
      break;
  }
  return true;
}

void ergodox_blink_all_leds_reverse(void) {
    ergodox_led_all_off();
    ergodox_led_all_set(LED_BRIGHTNESS_DEFAULT);
    ergodox_right_led_3_on();
    wait_ms(50);
    ergodox_right_led_2_on();
    wait_ms(50);
    ergodox_right_led_1_on();
    wait_ms(50);
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  wait_ms(300);
  ergodox_blink_all_leds_reverse();
  wait_ms(300);

  ergodox_led_all_on();
  rgblight_init();
  rgblight_disable();

  for (int i = LED_BRIGHTNESS_HI; i > LED_BRIGHTNESS_LO; i--) {
    ergodox_led_all_set(i);
    wait_ms(5);
  }

  for (int i = LED_BRIGHTNESS_LO; i > 0; i--) {
    ergodox_led_all_set(i);
    wait_ms(10);
  }

  ergodox_led_all_off();
  ergodox_led_all_set(LED_BRIGHTNESS_HI);
};


void german_umlaut_lin(uint16_t code, bool uppercase) {
  tap_code(KC_RALT);
  register_code(KC_LSFT);
  tap_code(KC_QUOT);
  unregister_code(KC_LSFT);
  if (uppercase) register_code(KC_LSFT);
  tap_code(code);
  if (uppercase) unregister_code(KC_LSFT);
}

LEADER_EXTERNS();

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_ESC) {
      os_type = (os_type + 1) % 2;

      bool rgb_was_enabled = rgblight_config.enable;
      int rgb_current_mode = rgblight_config.mode;

      if (rgb_was_enabled) rgblight_disable();
      wait_ms(300);
      rgblight_enable();

      if (os_type == OS_WIN) rgblight_setrgb(0, 0, 255);
      else if (os_type == OS_LIN) rgblight_setrgb(0, 255, 0);

      wait_ms(100);

      rgblight_disable();
      wait_ms(600);

      rgblight_mode(rgb_current_mode);
      if (rgb_was_enabled) rgblight_enable();
    }

    SEQ_ONE_KEY(KC_O) {
      switch (os_type) {
      case OS_WIN:
        tap_code(KC_NLCK);
        register_code(KC_RALT);
        tap_code(KC_KP_0);
        tap_code(KC_KP_2);
        tap_code(KC_KP_4);
        tap_code(KC_KP_6);
        unregister_code(KC_RALT);
        tap_code(KC_NLCK);
        break;
      case OS_LIN:
        german_umlaut_lin(KC_O, false);
        break;
      }
    }

    SEQ_TWO_KEYS(KC_O, KC_O) {
      switch (os_type) {
      case OS_WIN:
        tap_code(KC_NLCK);
        register_code(KC_RALT);
        tap_code(KC_KP_0);
        tap_code(KC_KP_2);
        tap_code(KC_KP_1);
        tap_code(KC_KP_4);
        unregister_code(KC_RALT);
        tap_code(KC_NLCK);
        break;
      case OS_LIN:
        german_umlaut_lin(KC_O, true);
        break;
      }
    }

    SEQ_ONE_KEY(KC_A) {
      switch (os_type) {
      case OS_WIN:
        tap_code(KC_NLCK);
        register_code(KC_RALT);
        tap_code(KC_KP_0);
        tap_code(KC_KP_2);
        tap_code(KC_KP_2);
        tap_code(KC_KP_8);
        unregister_code(KC_RALT);
        tap_code(KC_NLCK);
        break;
      case OS_LIN:
        german_umlaut_lin(KC_A, false);
        break;
      }
    }

    SEQ_TWO_KEYS(KC_A, KC_A) {
      switch (os_type) {
      case OS_WIN:
        tap_code(KC_NLCK);
        register_code(KC_RALT);
        tap_code(KC_KP_0);
        tap_code(KC_KP_1);
        tap_code(KC_KP_9);
        tap_code(KC_KP_6);
        unregister_code(KC_RALT);
        tap_code(KC_NLCK);
        break;
      case OS_LIN:
        german_umlaut_lin(KC_A, true);
        break;
      }
    }

    SEQ_ONE_KEY(KC_U) {
      switch (os_type) {
      case OS_WIN:
        tap_code(KC_NLCK);
        register_code(KC_RALT);
        tap_code(KC_KP_0);
        tap_code(KC_KP_2);
        tap_code(KC_KP_5);
        tap_code(KC_KP_2);
        unregister_code(KC_RALT);
        tap_code(KC_NLCK);
        break;
      case OS_LIN:
        german_umlaut_lin(KC_U, false);
        break;
      }
    }

    SEQ_TWO_KEYS(KC_U, KC_U) {
      switch (os_type) {
      case OS_WIN:
        tap_code(KC_NLCK);
        register_code(KC_RALT);
        tap_code(KC_KP_0);
        tap_code(KC_KP_2);
        tap_code(KC_KP_2);
        tap_code(KC_KP_0);
        unregister_code(KC_RALT);
        tap_code(KC_NLCK);
        break;
      case OS_LIN:
        german_umlaut_lin(KC_U, true);
        break;
      }
    }

    SEQ_ONE_KEY(KC_S) {
      switch (os_type) {
      case OS_WIN:
        tap_code(KC_NLCK);
        register_code(KC_RALT);
        tap_code(KC_KP_0);
        tap_code(KC_KP_2);
        tap_code(KC_KP_2);
        tap_code(KC_KP_3);
        unregister_code(KC_RALT);
        tap_code(KC_NLCK);
        break;
      case OS_LIN:
        tap_code(KC_RALT);
        tap_code(KC_S);
        tap_code(KC_S);
        break;
      }
    }

    SEQ_ONE_KEY(KC_E) {
      switch (os_type) {
      case OS_WIN:
        tap_code(KC_NLCK);
        register_code(KC_RALT);
        tap_code(KC_KP_0);
        tap_code(KC_KP_1);
        tap_code(KC_KP_2);
        tap_code(KC_KP_8);
        unregister_code(KC_RALT);
        tap_code(KC_NLCK);
        break;
      case OS_LIN:
        tap_code(KC_RALT);
        tap_code(KC_E);
        tap_code(KC_EQL);
        break;
      }
    }
  }
};

void rgb_enable_gaming(void) {
  rgblight_enable();
  rgblight_mode(12);
}

void rgb_disable_gaming(void) {
  rgblight_disable();
}

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
          rgb_disable_gaming();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        #ifdef RGBLIGHT_ENABLE
          rgb_disable_gaming();
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        #ifdef RGBLIGHT_ENABLE
          rgb_disable_gaming();
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        #ifdef RGBLIGHT_ENABLE
          rgb_disable_gaming();
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        #ifdef RGBLIGHT_ENABLE
          rgb_enable_gaming();
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        #ifdef RGBLIGHT_ENABLE
          rgb_disable_gaming();
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        #ifdef RGBLIGHT_ENABLE
          rgb_disable_gaming();
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        #ifdef RGBLIGHT_ENABLE
          rgb_disable_gaming();
        #endif
        break;
      default:
        #ifdef RGBLIGHT_ENABLE
          rgb_disable_gaming();
        #endif
        break;
    }

  return state;
};
