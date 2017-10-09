#include "stdafx.h"

#include "../../Common/Includes.h"

#include "ivector.h"

namespace LTILib
{

	int ivector_create(lua_State *L)
	{
		lti::ivector* pVector = new lti::ivector;

		LuaKit::PushApiData<IVectorApiSngl>(L, pVector);

		return 1;
	}

	int ivector_release(lua_State *L)
	{
		LuaKit::ReleaseWrapper<IVectorApiSngl, LuaKit::Delete>(L, 1);

		return 0;
	}

	int ivector_resize(lua_State *L)
	{
		unsigned int params = LuaKit::GetParamsCount(L);

		if ( params < 3 )
			return luaL_error(L, "Too few input arguments were passed.");

		lti::ivector* pVector = LuaKit::PopApiData<IVectorApiSngl>(L, 1);
		int size = (int)lua_tonumber(L, 2);

		int value = 0;
		bool copyData = true;
		bool initNew = true;

		if ( params >= 3 )
			value = (int)lua_tonumber(L, 3);

		if ( params >= 4 )
			copyData = ( lua_toboolean(L, 4) != 0 );

		if ( params >= 5 )
			initNew = ( lua_toboolean(L, 5) != 0 );

        pVector->resize(size, value, copyData, initNew);

		return 0;
	}

	int ivector_setat(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);
		luaL_checktype(L, 3, LUA_TNUMBER);

		lti::ivector* pVector = LuaKit::PopApiData<IVectorApiSngl>(L, 1);
		int index = (int)lua_tonumber(L, 2);
		int value = (int)lua_tonumber(L, 3);

		if ( index >= pVector->size() )
			return 0;

		pVector->at(index) = value;

		return 0;
	}

	int ivector_getat(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);

		lti::ivector* pVector = LuaKit::PopApiData<IVectorApiSngl>(L, 1);
		int index = (int)lua_tonumber(L, 2);

		if ( index >= pVector->size() )
			return 0;

		int value = pVector->at(index);

		lua_pushnumber(L, value);
        
		return 1;
	}

	int ivector_size(lua_State *L)
	{
		lti::ivector* pVector = LuaKit::PopApiData<IVectorApiSngl>(L, 1);

		int size = pVector->size();

		lua_pushnumber(L, size);

		return 1;
	}

	class IVectorOps
	{
	public:
		IVectorOps()
		{
			IVectorApiSngl::Instance().AddGlobal("createIVector", ivector_create);

			IVectorApiSngl::Instance().AddMethod("__gc", ivector_release);
			IVectorApiSngl::Instance().AddMethod("resize", ivector_resize);
			IVectorApiSngl::Instance().AddMethod("setat", ivector_setat);
			IVectorApiSngl::Instance().AddMethod("getat", ivector_getat);
			IVectorApiSngl::Instance().AddMethod("size", ivector_size);
		}
	};

	IVectorOps ivectorOps;

} // namespace LTILib
