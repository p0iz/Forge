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

#include <X11/keysym.h>
#include <unordered_set>


namespace Forge {

/* All keys for a regular U.S. QWERTY keyboard */
enum class Key
{
  /* Row 1 */
  Escape = 9,
  F1 = 67,
  F2 = 68,
  F3 = 69,
  F4 = 70,
  F5 = XK_F5,
  F6 = XK_F6,
  F7 = XK_F7,
  F8 = XK_F8,
  F9 = XK_F9,
  F10 = XK_F10,
  F11 = XK_F11,
  F12 = XK_F12,

  /* Row 2 */
  Grave = XK_grave,
  _1 = XK_1,
  _2 = XK_2,
  _3 = XK_3,
  _4 = XK_4,
  _5 = XK_5,
  _6 = XK_6,
  _7 = XK_7,
  _8 = XK_8,
  _9 = XK_9,
  _0 = XK_0,
  Minus = XK_minus,
  Equals = XK_equal,
  Backspace = XK_BackSpace,

  /* Row 3 */
  Tab = XK_Tab,
  Q = XK_q,
  W = XK_w,
  E = XK_e,
  R = XK_r,
  T = XK_t,
  Y = XK_y,
  U = XK_u,
  I = XK_i,
  O = XK_o,
  P = XK_p,
  LeftBracket = XK_bracketleft,
  RightBracket = XK_bracketright,
  Backslash = XK_backslash,

  /* Row 4 */
  CapsLock = XK_Caps_Lock,
  A = 38,
  S = 39,
  D = 40,
  F = XK_f,
  G = XK_g,
  H = XK_h,
  J = XK_j,
  K = XK_k,
  L = XK_l,
  Semicolon = XK_semicolon,
  Apostrophe = XK_apostrophe,
  Enter = XK_Return,

  /* Row 5 */
  LeftShift = XK_Shift_L,
  Z = XK_z,
  X = XK_x,
  C = XK_c,
  V = XK_v,
  B = XK_b,
  N = XK_n,
  M = XK_m,
  Comma = XK_comma,
  Period = XK_period,
  Slash = XK_slash,
  RightShift = XK_Shift_R,

  /* Row 6 */
  LeftControl = XK_Control_L,
  LeftMeta = XK_Meta_L,
  Alt = XK_Alt_L,
  Space = 65,
  AltGr = XK_Alt_R,
  RightMeta = XK_Meta_R,
  Menu = XK_Menu,
  RightControl = XK_Control_R,

  /* Motion keys */
  Insert = XK_Insert,
  Home = XK_Home,
  PageUp = XK_Page_Up,
  Delete = XK_Delete,
  End = XK_End,
  PageDown = XK_Page_Down,
  Up = 111,
  Left = 113,
  Down = 116,
  Right = 114,

  /* Keypad (numlock off) */
  NumLock = XK_Num_Lock,
  KP_Slash = XK_KP_Divide,
  KP_Asterisk = XK_KP_Multiply,
  KP_Minus = XK_KP_Subtract,
  KP_Plus = XK_KP_Add,
  KP_1 = XK_KP_1,
  KP_2 = XK_KP_2,
  KP_3 = XK_KP_3,
  KP_4 = XK_KP_4,
  KP_5 = XK_KP_5,
  KP_6 = XK_KP_6,
  KP_7 = XK_KP_7,
  KP_8 = XK_KP_8,
  KP_9 = XK_KP_9,
  KP_0 = XK_KP_0,
  KP_Comma = XK_KP_Decimal,
  KP_Enter = XK_KP_Enter,

  /* Keypad (numlock on) */
  KP_Home = XK_KP_Home,
  KP_End = XK_KP_End,
  KP_PageUp = XK_KP_Page_Up,
  KP_PageDown = XK_KP_Page_Down,
  KP_Up = XK_KP_Up,
  KP_Left = XK_KP_Left,
  KP_Right = XK_KP_Right,
  KP_Down = XK_KP_Down,
  KP_Insert = XK_KP_Insert,
  KP_Delete = XK_KP_Delete
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
