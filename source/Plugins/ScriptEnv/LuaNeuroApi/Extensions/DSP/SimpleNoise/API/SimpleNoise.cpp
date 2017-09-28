#include "StdAfx.h"
#include "SimpleNoise.h"

#include "..\..\..\..\GlobalStorage.h"
#include "..\..\..\..\ApiMacro.h"

#include "../API/Generators.h"
#include "../API/PerlinNoise.h"

#include "../Engine/VRand.h"

int LuaSimpleNoise_CreateGenerator(lua_State *L)
{
	SimpleNoise::VRand* pGenerator = new SimpleNoise::VRand;
	pGenerator->seed();

	PUSH_ARGUMENT(SimpleNoise::VRand*, pGenerator, -2);

	return 1;
}

int LuaSimpleNoise_ReleaseGenerator(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	POP_ARGUMENT(SimpleNoise::VRand*, pGenerator, 1)

	delete pGenerator;

	return 0;
}


// Package initialization
static const luaL_reg simplenoiselib[] = {
	{"createGenerator",				LuaSimpleNoise_CreateGenerator},
	{"releaseGenerator",			LuaSimpleNoise_ReleaseGenerator},

	{"getWhite",					LuaSimpleNoise_GetWhite},
	{"getPink",						LuaSimpleNoise_GetPink},
	{"getBrown",					LuaSimpleNoise_GetBrown},

	{"perlinStep",					LuaSimpleNoise_PerlinStep},
	{"setPerlinSeed",				LuaSimpleNoise_SetPerlinSeed},

	{NULL, NULL}
}; 

int luaopen_simplenoise(lua_State *L) 
{
	luaL_openlib(L, "snoise", simplenoiselib, 0);

	return 1;
} 
