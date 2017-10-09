#include "stdafx.h"

#include "../../Common/Includes.h"

#include "Pen.h"

namespace Drawing
{

	int pen_create(lua_State *L)
	{
		float width = 1.0f;
		unsigned char red = 0;
		unsigned char green = 0;
		unsigned char blue = 0;

		uint params = LuaKit::GetParamsCount(L);
		
		if ( params >= 1 )
			width = (float)lua_tonumber(L, 1);

		if ( params >= 4 )
		{
			red = (unsigned char)lua_tonumber(L, 2);
			green = (unsigned char)lua_tonumber(L, 3);
			blue = (unsigned char)lua_tonumber(L, 4);
		}
		
		Gdiplus::Pen* pPen = new Gdiplus::Pen(Gdiplus::Color(red, green, blue), width);

		LuaKit::PushApiData<PenApiSngl>(L, pPen);

        return 1;
	}

	int pen_release(lua_State *L)
	{
		LuaKit::ReleaseWrapper<PenApiSngl, LuaKit::Delete>(L, 1);
		return 0;
	}

	class PenMethods
	{
	public:

		PenMethods()
		{
			PenApiSngl::Instance().AddGlobal("createPen", pen_create);

			PenApiSngl::Instance().AddMethod("__gc", pen_release);
		}

	};

	PenMethods penMethods;

} // namespace Drawing
