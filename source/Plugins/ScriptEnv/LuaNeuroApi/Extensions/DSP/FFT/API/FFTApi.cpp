#include "StdAfx.h"
#include "FFTApi.h"

#include "..\..\..\..\GlobalStorage.h"
#include "..\..\..\..\ApiMacro.h"

#include "../Engine/FFT.h"

int LuaFFT_FFT(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)	

    POP_ARGUMENT(IDataFactory*, piDataFactory, 1)
	int direction = (int)lua_tonumber(L, 2);

	ulong length = piDataFactory->GetDataLength() / 2;
	if ( iNumber == 3 )
	{
		length = (ulong)lua_tonumber(L, 2);
		if ( length > (ulong)piDataFactory->GetDataLength() / 2 )
			return 0;
	}

	FFT_T(
		(Complex*)piDataFactory->GetData(), 
		length, 
		direction);		

	return 0;
}

int LuaFFT_FFTReal(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)	

	POP_ARGUMENT(IDataFactory*, piDataFactory, 1)
	int direction = (int)lua_tonumber(L, 2);

	ulong length = piDataFactory->GetDataLength();
	if ( iNumber == 3 )
	{
		length = (ulong)lua_tonumber(L, 2);
		if ( length > (ulong)piDataFactory->GetDataLength() )
			return 0;
	}

	RealFFT(
		piDataFactory->GetData(),
		length,
		direction);

	return 0;
}

int LuaFFT_UnpackResult(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)	

	POP_ARGUMENT(IDataFactory*, piSrcFactory, 1)

	CDataFactory* pDataFactory = new CDataFactory();
	CLuaStorage_FactoriesContainer::AddObject(pDataFactory);

	int length = piSrcFactory->GetDataLength();
	
	pDataFactory->CreateFactory(length + 2);
	memcpy(
		pDataFactory->GetData(),
		piSrcFactory->GetData(),
		length * sizeof(float));

	float ynh2 = pDataFactory->GetItemData(1);
	pDataFactory->SetItemData(1, 0.0f);
	pDataFactory->SetItemData(length, ynh2);    
	
	IDataFactory* piDataFactory = NULL;
	pDataFactory->QueryInterface(IDD_IDataFactory, (void**)&piDataFactory);

	PUSH_ARGUMENT(IDataFactory*, piDataFactory, -2)

    return 1;
}

/*int LuaSimpleNoise_CreateGenerator(lua_State *L)
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
}*/

static const luaL_const fftenums[] = {
	{"DIRECT",					1},
	{"INVERSE",					-1},

	{NULL, NULL}
};



// Package initialization
static const luaL_reg fftlib[] = {
	{"fft",							LuaFFT_FFT},
	{"fftr",						LuaFFT_FFTReal},
	{"unpack",						LuaFFT_UnpackResult},

	{NULL, NULL}
}; 

int luaopen_fft(lua_State *L) 
{
	luaL_openlib(L, "fft", fftlib, 0);

	lua_pushstring(L, "fft");
	lua_gettable(L, LUA_GLOBALSINDEX);  
	lua_insert(L, -1);

	for (const luaL_const* l = fftenums; l->name_; l++) {
		lua_pushstring(L, l->name_);
		lua_pushnumber(L, l->value_);
		lua_settable(L, -3);
	} 

	lua_pop(L, 0);

	return 1;
} 
