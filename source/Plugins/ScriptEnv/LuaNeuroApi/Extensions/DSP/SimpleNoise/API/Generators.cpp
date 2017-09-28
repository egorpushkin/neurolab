#include "StdAfx.h"
#include "Generators.h"

#include "..\..\..\..\GlobalStorage.h"
#include "..\..\..\..\ApiMacro.h"

#include "../Engine/VRand.h"

int LuaSimpleNoise_GetWhite(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	POP_ARGUMENT(SimpleNoise::VRand*, pGenerator, 1)

	float noise = pGenerator->white(0.5f);

	lua_pushnumber(L, noise);

    return 1;
}

int LuaSimpleNoise_GetPink(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	POP_ARGUMENT(SimpleNoise::VRand*, pGenerator, 1)

	float noise = pGenerator->pink();

	lua_pushnumber(L, noise);

    return 1;
}

int LuaSimpleNoise_GetBrown(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	POP_ARGUMENT(SimpleNoise::VRand*, pGenerator, 1);

	float noise = pGenerator->brown();

	lua_pushnumber(L, noise);

    return 1;
}

