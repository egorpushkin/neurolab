#include "stdafx.h"

#include "../../Common/Includes.h"

#include "dmatrix.h"

namespace LTILib
{
	
	int dmatrix_create(lua_State *L)
	{
		lti::dmatrix* pMatrix = new lti::dmatrix;

		LuaKit::PushApiData<DMatrixApiSngl>(L, pMatrix);

		return 1;
	}

	int dmatrix_release(lua_State *L)
	{
		LuaKit::ReleaseWrapper<DMatrixApiSngl, LuaKit::Delete>(L, 1);

		return 0;
	}

	int dmatrix_resize(lua_State *L)
	{
		unsigned int params = LuaKit::GetParamsCount(L);

		if ( params < 3 )
			return luaL_error(L, "Too few input arguments were passed.");

		lti::dmatrix* pMatrix = LuaKit::PopApiData<DMatrixApiSngl>(L, 1);
		int rows = (int)lua_tonumber(L, 2);
		int cols = (int)lua_tonumber(L, 3);

		double value = 0.0;
		bool copyData = true;
		bool initNew = true;

		if ( params >= 4 )
			value = lua_tonumber(L, 4);

		if ( params >= 5 )
			copyData = ( lua_toboolean(L, 5) != 0 );

		if ( params >= 6 )
			initNew = ( lua_toboolean(L, 6) != 0 );

        pMatrix->resize(rows, cols, value, copyData, initNew);

		return 0;
	}

	int dmatrix_setat(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);
		luaL_checktype(L, 3, LUA_TNUMBER);
		luaL_checktype(L, 4, LUA_TNUMBER);

		lti::dmatrix* pMatrix = LuaKit::PopApiData<DMatrixApiSngl>(L, 1);
		int row = (int)lua_tonumber(L, 2);
		int col = (int)lua_tonumber(L, 3);
		double value = lua_tonumber(L, 4);

		if ( row >= pMatrix->rows() )
			return 0;

		if ( col >= pMatrix->columns() )
			return 0;

		pMatrix->at(row, col) = value;

		return 0;
	}

	int dmatrix_getat(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);
		luaL_checktype(L, 3, LUA_TNUMBER);

		lti::dmatrix* pMatrix = LuaKit::PopApiData<DMatrixApiSngl>(L, 1);
		int row = (int)lua_tonumber(L, 2);
		int col = (int)lua_tonumber(L, 3);

		if ( row >= pMatrix->rows() )
			return 0;

		if ( col >= pMatrix->columns() )
			return 0;

		double value = pMatrix->at(row, col);

		lua_pushnumber(L, value);
        
		return 1;
	}

	int dmatrix_rows(lua_State *L)
	{
		lti::dmatrix* pMatrix = LuaKit::PopApiData<DMatrixApiSngl>(L, 1);

		int rows = pMatrix->rows();

		lua_pushnumber(L, rows);

		return 1;
	}

	int dmatrix_columns(lua_State *L)
	{
		lti::dmatrix* pMatrix = LuaKit::PopApiData<DMatrixApiSngl>(L, 1);

		int cols = pMatrix->columns();

		lua_pushnumber(L, cols);

		return 1;
	}

	class DMatrixOps
	{
	public:
		DMatrixOps()
		{
			DMatrixApiSngl::Instance().AddGlobal("createDMatrix", dmatrix_create);

			DMatrixApiSngl::Instance().AddMethod("__gc", dmatrix_release);
			DMatrixApiSngl::Instance().AddMethod("resize", dmatrix_resize);
			DMatrixApiSngl::Instance().AddMethod("setat", dmatrix_setat);
			DMatrixApiSngl::Instance().AddMethod("getat", dmatrix_getat);
			DMatrixApiSngl::Instance().AddMethod("rows", dmatrix_rows);
			DMatrixApiSngl::Instance().AddMethod("columns", dmatrix_columns);
		}
	};

	DMatrixOps dmatrixOps;

} // namespace LTILib
