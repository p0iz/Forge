/* This file is part of Forge.
 *
 * Forge is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Forge is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with Forge.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 Tommi Martela
 *
 */

#pragma once

#include <SDL2/SDL_keycode.h>

namespace Forge {

/* All keys for a regular U.S. QWERTY keyboard */
enum class Key
{
  /* Row 1 */
  Escape = SDLK_ESCAPE,
  F1 = SDLK_F1,
  F2 = SDLK_F2,
  F3 = SDLK_F3,
  F4 = SDLK_F4,
  F5 = SDLK_F5,
  F6 = SDLK_F6,
  F7 = SDLK_F7,
  F8 = SDLK_F8,
  F9 = SDLK_F9,
  F10 = SDLK_F10,
  F11 = SDLK_F11,
  F12 = SDLK_F12,

  /* Row 2 */
  Grave = SDLK_BACKQUOTE,
  _1 = SDLK_1,
  _2 = SDLK_2,
  _3 = SDLK_3,
  _4 = SDLK_4,
  _5 = SDLK_5,
  _6 = SDLK_6,
  _7 = SDLK_7,
  _8 = SDLK_8,
  _9 = SDLK_9,
  _0 = SDLK_0,
  Minus = SDLK_MINUS,
  Equals = SDLK_EQUALS,
  Backspace = SDLK_BACKSPACE,

  /* Row 3 */
  Tab = SDLK_TAB,
  Q = SDLK_q,
  W = SDLK_w,
  E = SDLK_e,
  R = SDLK_r,
  T = SDLK_t,
  Y = SDLK_y,
  U = SDLK_u,
  I = SDLK_i,
  O = SDLK_o,
  P = SDLK_p,
  LeftBracket = SDLK_LEFTBRACKET,
  RightBracket = SDLK_RIGHTBRACKET,
  Backslash = SDLK_BACKSLASH,

  /* Row 4 */
  CapsLock = SDLK_CAPSLOCK,
  A = SDLK_a,
  S = SDLK_s,
  D = SDLK_d,
  F = SDLK_f,
  G = SDLK_g,
  H = SDLK_h,
  J = SDLK_j,
  K = SDLK_k,
  L = SDLK_l,
  Semicolon = SDLK_SEMICOLON,
  Apostrophe = SDLK_QUOTE,
  Enter = SDLK_RETURN,

  /* Row 5 */
  LeftShift = SDLK_LSHIFT,
  Z = SDLK_z,
  X = SDLK_x,
  C = SDLK_c,
  V = SDLK_v,
  B = SDLK_b,
  N = SDLK_n,
  M = SDLK_m,
  Comma = SDLK_COMMA,
  Period = SDLK_PERIOD,
  Slash = SDLK_SLASH,
  RightShift = SDLK_RSHIFT,

  /* Row 6 */
  LeftControl = SDLK_LCTRL,
  LeftMeta = SDLK_LGUI,
  Alt = SDLK_LALT,
  Space = SDLK_SPACE,
  AltGr = SDLK_RALT,
  RightMeta = SDLK_RGUI,
  Menu = SDLK_MENU,
  RightControl = SDLK_RCTRL,

  /* Motion keys */
  Insert = SDLK_INSERT,
  Home = SDLK_HOME,
  PageUp = SDLK_PAGEUP,
  Delete = SDLK_DELETE,
  End = SDLK_END,
  PageDown = SDLK_PAGEDOWN,
  Up = SDLK_UP,
  Left = SDLK_LEFT,
  Down = SDLK_DOWN,
  Right = SDLK_RIGHT,

  /* Keypad (numlock off) */
  NumLock = SDLK_NUMLOCKCLEAR,
  KP_Divide = SDLK_KP_DIVIDE,
  KP_Multiply = SDLK_KP_MULTIPLY,
  KP_Minus = SDLK_KP_MINUS,
  KP_Plus = SDLK_KP_PLUS,
  KP_1 = SDLK_KP_1,
  KP_2 = SDLK_KP_2,
  KP_3 = SDLK_KP_3,
  KP_4 = SDLK_KP_4,
  KP_5 = SDLK_KP_5,
  KP_6 = SDLK_KP_6,
  KP_7 = SDLK_KP_7,
  KP_8 = SDLK_KP_8,
  KP_9 = SDLK_KP_9,
  KP_0 = SDLK_KP_0,
  KP_Comma = SDLK_KP_DECIMAL,
  KP_Enter = SDLK_KP_ENTER
};

enum class Modifier
{
  Shift = 0x1,
  Alt = 0x2,
  Control = 0x4,
  Meta = 0x8
};

}

/* Provide a hash function for keys */
namespace std
{
  template<>
  class hash<Forge::Key>
  {
    public:
      size_t operator()(Forge::Key key) const noexcept
      {
        return static_cast<size_t>(key);
      }
  };
}
