/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "stdlib.h"
#include "stdio.h"

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _NUMPAD,
  _INTERACT
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  EXT_PLV,
  NUMPAD,
};

enum unicode_names {
  L_ENNE,
  H_ENNE,
  S_EXCL,
  E_EXCL,
  S_QSTN,
  E_QSTN
};

const uint32_t PROGMEM unicode_map[] = {
  [S_EXCL] = 0x00A1, // ¡
  [E_EXCL] = 0x0021, // !
  [S_QSTN] = 0x00BF, // ¿
  [E_QSTN] = 0x003F  // ?
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define INTERACT MO(_INTERACT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |Esc   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Bksp  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Tab   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  /   |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Ctrl  | Meta | Alt  |Inter |Lower |    Space    |Raise | Left | Low  |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, INTERACT,LOWER,   KC_SPC,  KC_SPC,  RAISE,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
),

/* Interact
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   ¿  |   ?  |      |      |      |      |      |      |      |   '  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   ¡  |   !  |      |      |      |      |      |      |   \  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgDn | PgUp | End |
 * `-----------------------------------------------------------------------------------'
 */
[_INTERACT] = LAYOUT_planck_grid(
  KC_GRV,    KC_1,      KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  _______, X(S_QSTN), X(E_QSTN), _______, _______, _______, _______, _______, _______, _______, KC_QUOT, KC_DQT,
  _______, X(S_EXCL), X(E_EXCL), _______, _______, _______, _______, _______, _______, KC_BSLS, _______, _______,
  _______,   _______,   _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   (  |   )  |   =  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   ¿  |   ?  |      |      |      |      |      |      |   [  |   ]  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   ¡  |   !  |      |      |      |      |      |      |   \  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
  KC_GRV,    KC_1,      KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_LPRN, KC_RPRN, KC_EQL,
  _______, X(S_QSTN), X(E_QSTN), _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______,
  _______, X(S_EXCL), X(E_EXCL), _______, _______, _______, _______, _______, _______, KC_BSLS, _______, _______,
  _______,   _______,   _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   ¡  |   !  |      |      |      |      |      |      |      |   '  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   ¿  |   ?  |      |      |      |      |      |      |   \  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
  KC_GRV,    KC_1,      KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  _______, X(S_QSTN), X(E_QSTN), _______, _______, _______, _______, _______, _______, _______, KC_QUOT, KC_DQT,
  _______, X(S_EXCL), X(E_EXCL), _______, _______, _______, _______, _______, _______, KC_BSLS, _______, _______,
  _______,   _______,   _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |QWERTY| F1   | F2   | F3   | F4   | F5   |      | F10  | F11  | F12  |PrScr | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |PROG  |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |NUMPAD|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    QWERTY,  _______, _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______,  _______, NUMPAD,  _______,
    DEBUG,   MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    RESET,   _______, _______, _______, _______, _______, _______, _______, _______,  RGB_M_SN, RGB_M_K, RGB_M_G
),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |  A   |  B   |  C   |  D   |  E   | XXXX |  _   |   7  |   8  |   9  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  =   |  +   |  -   |  *   |  /   | XXXX |  .   |   4  |   5  |   6  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  =   |  (   |  )   |  &   |  |   | XXXX |  ,   |   1  |   2  |   3  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  =   |  [   |  ]   |      |             |      |   #  |   0  |   $  | XXXX |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid(
  _______, KC_A,    KC_B,    KC_C,     KC_D,    KC_E,    XXXXXXX, KC_UNDS, KC_7,    KC_8,    KC_9,    _______,
  _______, KC_EQL,  KC_PLUS, KC_MINS,  KC_ASTR, KC_SLSH, XXXXXXX, KC_DOT,  KC_4,    KC_5,    KC_6,    _______,
  _______, KC_EQL,  KC_LPRN, KC_RPRN,  KC_AMPR, KC_PIPE, XXXXXXX, KC_COMM, KC_1,    KC_2,    KC_3,    _______,
  _______, KC_EQL,  KC_LBRC, KC_RBRC,  _______, _______, _______, _______, KC_HASH, KC_0,    KC_DLR,  XXXXXXX 
)

};


#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case NUMPAD:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_NUMPAD);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_user(void) {
  #ifdef AUDIO_ENABLE
    if (muse_mode) {
      if (muse_counter == 0) {
        uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
        if (muse_note != last_muse_note) {
          stop_note(compute_freq_for_midi_note(last_muse_note));
          play_note(compute_freq_for_midi_note(muse_note), 0xF);
          last_muse_note = muse_note;
        }
      }
      muse_counter = (muse_counter + 1) % muse_tempo;
    }
  #endif

  uint16_t layer = biton32(layer_state);

  // INSERT CODE HERE: turn off all leds
  switch (layer) {
    case QWERTY:
      //only works with void rgb_matrix_indicators_user(void) {
      rgb_matrix_set_color(42, 0x00, 0xFF, 0xFF);
      rgb_matrix_set_color(41, 0xFF, 0xFF, 0x00);
      rgb_matrix_set_color(40, 0x00, 0xFF, 0x00);
      rgb_matrix_set_color(39, 0x00, 0xFF, 0xFF);
      rgb_matrix_set_color(38, 0xFF, 0xFF, 0x00);
      rgb_matrix_set_color(37, 0x00, 0xFF, 0x00);
      rgb_matrix_set_color(36, 0x00, 0xFF, 0xFF);
      rgb_matrix_set_color(35, 0xFF, 0xFF, 0x00);
      rgb_matrix_set_color(34, 0x00, 0xFF, 0x00);
      break;
  }
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

// Unnecesary after executing any of these modes
// UC_M_OS // Mac OS X 
// UC_M_LN // Linux
// UC_M_BS // BSD
// UC_M_WC // Windows
void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX); 
    //set_unicode_input_mode(UC_OSX); 
    //set_unicode_input_mode(UC_WINC); 
};