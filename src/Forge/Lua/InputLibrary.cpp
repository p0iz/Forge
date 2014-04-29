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
 * Copyright 2014 Tommi Martela
 *
 */

#include "InputLibrary.hpp"
#include "Platform/Input/InputHandler.hpp"
#include <lua.hpp>

// Helper macro to add keycodes to Lua table
#define SET_KEY(Code)\
{\
  Key* key = static_cast<Key*>(lua_newuserdata(state, sizeof(Key)));\
  *key = Key::Code;\
  luaL_setmetatable(state, "Input.Key");\
  lua_setfield(state, -2, #Code);\
}\

namespace Forge {

InputLibrary::InputLibrary()
{
}

InputLibrary::~InputLibrary()
{
}

void InputLibrary::import(lua_State* state)
{
  lua_newtable(state);

  pushKeyCodeTable(state);
  lua_setfield(state, -2, "Key");

  LIB_FUNC(state, isKeyDown);

  lua_setglobal(state, "Input");
}

void InputLibrary::remove(lua_State* state)
{
  lua_pushnil(state); 
  lua_setglobal(state, "Input");
}

int InputLibrary::isKeyDown(lua_State* state)
{
  Key* k = static_cast<Key*>(luaL_checkudata(state, 1, "Input.Key"));
  lua_pushboolean(state, InputHandler::instance().isKeyDown(*k));
  return 1;
}

void InputLibrary::pushKeyCodeTable(lua_State* state)
{
  luaL_newmetatable(state, "Input.Key");
  lua_newtable(state);

  /* Row 1 */
  SET_KEY(Escape);
  SET_KEY(F1);
  SET_KEY(F2);
  SET_KEY(F3);
  SET_KEY(F4);
  SET_KEY(F5);
  SET_KEY(F6);
  SET_KEY(F7);
  SET_KEY(F8);
  SET_KEY(F9);
  SET_KEY(F10);
  SET_KEY(F11);
  SET_KEY(F12);

  /* Row 2 */
  SET_KEY(Grave);
  SET_KEY(_1);
  SET_KEY(_2);
  SET_KEY(_3);
  SET_KEY(_4);
  SET_KEY(_5);
  SET_KEY(_6);
  SET_KEY(_7);
  SET_KEY(_8);
  SET_KEY(_9);
  SET_KEY(_0);
  SET_KEY(Minus);
  SET_KEY(Equals);
  SET_KEY(Backspace);

  /* Row 3 */
  SET_KEY(Tab);
  SET_KEY(Q);
  SET_KEY(W);
  SET_KEY(E);
  SET_KEY(R);
  SET_KEY(T);
  SET_KEY(Y);
  SET_KEY(U);
  SET_KEY(I);
  SET_KEY(O);
  SET_KEY(P);
  SET_KEY(LeftBracket);
  SET_KEY(RightBracket);
  SET_KEY(Backslash);

  /* Row 4 */
  SET_KEY(CapsLock);
  SET_KEY(A);
  SET_KEY(S);
  SET_KEY(D);
  SET_KEY(F);
  SET_KEY(G);
  SET_KEY(H);
  SET_KEY(J);
  SET_KEY(K);
  SET_KEY(L);
  SET_KEY(Semicolon);
  SET_KEY(Apostrophe);
  SET_KEY(Enter);

  /* Row 5 */
  SET_KEY(LeftShift);
  SET_KEY(Z);
  SET_KEY(X);
  SET_KEY(C);
  SET_KEY(V);
  SET_KEY(B);
  SET_KEY(N);
  SET_KEY(M);
  SET_KEY(Comma);
  SET_KEY(Period);
  SET_KEY(Slash);
  SET_KEY(RightShift);

  /* Row 6 */
  SET_KEY(LeftControl);
  SET_KEY(LeftMeta);
  SET_KEY(Alt);
  SET_KEY(Space);
  SET_KEY(AltGr);
  SET_KEY(RightMeta);
  SET_KEY(Menu);
  SET_KEY(RightControl);

  /* Motion keys */
  SET_KEY(Insert);
  SET_KEY(Home);
  SET_KEY(PageUp);
  SET_KEY(Delete);
  SET_KEY(End);
  SET_KEY(PageDown);
  SET_KEY(Up);
  SET_KEY(Left);
  SET_KEY(Down);
  SET_KEY(Right);

  /* Keypad (numlock off) */
  SET_KEY(NumLock);
  SET_KEY(KP_Divide);
  SET_KEY(KP_Multiply);
  SET_KEY(KP_Minus);
  SET_KEY(KP_Plus);
  SET_KEY(KP_1);
  SET_KEY(KP_2);
  SET_KEY(KP_3);
  SET_KEY(KP_4);
  SET_KEY(KP_5);
  SET_KEY(KP_6);
  SET_KEY(KP_7);
  SET_KEY(KP_8);
  SET_KEY(KP_9);
  SET_KEY(KP_0);
  SET_KEY(KP_Comma);
  SET_KEY(KP_Enter);

}

}
