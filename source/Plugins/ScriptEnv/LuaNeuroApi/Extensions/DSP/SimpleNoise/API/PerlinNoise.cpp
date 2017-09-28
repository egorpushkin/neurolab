#include "StdAfx.h"
#include "PerlinNoise.h"

#include "..\..\..\..\GlobalStorage.h"
#include "..\..\..\..\ApiMacro.h"

#include "../Engine/PerlinNoise.h"

int LuaSimpleNoise_PerlinStep(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(5)	

	float persistence = (float)lua_tonumber(L, 1);
	int octaves = (int)lua_tonumber(L, 2);
	float zoom = (float)lua_tonumber(L, 3);
	int x = (int)lua_tonumber(L, 4);
	int y = (int)lua_tonumber(L, 5);

	float total = PerlinNoise::NoisingStep(persistence, octaves, zoom, x, y);

	lua_pushnumber(L, total);
    
    return 1;
}

int LuaSimpleNoise_SetPerlinSeed(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	int seed = (int)lua_tonumber(L, 1);

	PerlinNoise::seed = seed;

	return 0;
}