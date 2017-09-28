#include "stdafx.h"

#include "../../Common/Includes.h"

#include "Graphics.h"
#include "../Pen/Pen.h"

namespace Drawing
{
	
	int graphics_drawLine(lua_State *L)
	{
		luaL_checktype(L, 3, LUA_TNUMBER);
		luaL_checktype(L, 4, LUA_TNUMBER);
		luaL_checktype(L, 5, LUA_TNUMBER);
		luaL_checktype(L, 6, LUA_TNUMBER);		
		
		Gdiplus::Graphics* pGraphics = LuaKit::PopApiData<GraphicsApiSngl>(L, 1);
		Gdiplus::Pen* pPen = LuaKit::PopApiData<PenApiSngl>(L, 2);

        if ( !pGraphics )
			return 0;

		float x1 = (float)lua_tonumber(L, 3);
		float y1 = (float)lua_tonumber(L, 4);
		float x2 = (float)lua_tonumber(L, 5);
		float y2 = (float)lua_tonumber(L, 6);

		pGraphics->DrawLine(pPen, x1, y1, x2, y2);

		return 0;
	}

	class GraphicsMethods
	{
	public:

		GraphicsMethods()
		{
			GraphicsApiSngl::Instance().AddMethod("drawLine", graphics_drawLine);
		}

	};

	GraphicsMethods graphicsMethods;

} // namespace LTILib
