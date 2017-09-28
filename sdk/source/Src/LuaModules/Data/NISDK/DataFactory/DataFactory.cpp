#include "Common/Includes.h"

namespace NISDK
{

	int df_loadFactoryFromPGM(lua_State *L);
	int df_createFactoryObject(lua_State *L);
	
	int df_saveToPGM(lua_State *L);	
	int df_release(lua_State *L);
	int df_createFactory(lua_State *L);
	int df_releaseFactory(lua_State *L);
	int df_setItemData(lua_State *L);
	int df_fillFactory(lua_State *L);
	int df_increaseValue(lua_State *L);
	int df_getItemData(lua_State *L);
	int df_getDataLength(lua_State *L);
	int df_moveFactoryData(lua_State *L);
	int df_toString(lua_State *L);
	int df_fromString(lua_State *L);

	const char* df_factory = "df{factory}";
	const char* df_any = "df{any}";

	static luaL_reg datafactoryGlobalApi[] = {
		{"loadFactoryFromPGM",			df_loadFactoryFromPGM},
		{"createFactory",				df_createFactoryObject},
		{"moveFactoryData",				df_moveFactoryData},
		{NULL, NULL}
	};

	static luaL_reg datafactoryObjectApi[] = {
		{"__gc",						df_release}, 
		{"saveToPGM",					df_saveToPGM},
		{"release",						df_release},
		{"createFactory",				df_createFactory},
		{"releaseFactory",				df_releaseFactory},
		{"setItemData",					df_setItemData},
		{"fillFactory",					df_fillFactory},
		{"increaseValue",				df_increaseValue},
		{"getItemData",					df_getItemData},
		{"getDataLength",				df_getDataLength},
		{"moveFactoryData",				df_moveFactoryData},
		{"toString",					df_toString},
		{"fromString",					df_fromString},
		{NULL, NULL}
	};

	int datafactory_open(lua_State * L)
	{
		auxiliar_newclass(L, df_factory, datafactoryObjectApi);
		auxiliar_add2group(L, df_factory, df_any);

		luaL_openlib(L, NULL, datafactoryGlobalApi, 0);  

		return 0;
	}

}
