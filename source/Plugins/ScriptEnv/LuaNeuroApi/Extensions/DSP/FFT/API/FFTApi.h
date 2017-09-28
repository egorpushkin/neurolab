#ifndef FFT_H__LUA_FFT_PACKEGE__INCLUDED_
#define FFT_H__LUA_FFT_PACKEGE__INCLUDED_

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

int				LuaFFT_FFT(lua_State *L);
int				LuaFFT_FFTReal(lua_State *L);
int				LuaFFT_UnpackResult(lua_State *L);

// Package initialization
int				luaopen_fft(lua_State *L);

#endif // !FFT_H__LUA_FFT_PACKEGE__INCLUDED_