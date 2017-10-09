#include "stdafx.h"

#include "../../Common/Includes.h"

#include "BufferCore.h"

#include "Buffer.h"

#include "../Graphics/Graphics.h"

namespace Drawing
{

	int bitmapbuffer_acquire(lua_State *L)
	{
		Gdiplus::Graphics* pGraphics = LuaKit::PopApiData<GraphicsApiSngl>(L, 1);		
		
		BitmapBuffer* pBitmapBuffer = AcquireBuffer(pGraphics);
		if ( !pBitmapBuffer )
			return 0;

		LuaKit::PushApiData<BitmapBufferApiSngl>(L, pBitmapBuffer);

        return 1;
	}

	template
	<
		class T
	>
	class ReleaseBitmapBuffer
	{
	public:

		static void DoRelease(T& pBitmapBuffer)
		{
			if ( pBitmapBuffer )
			{
				ReleaseBuffer(pBitmapBuffer);
			}
		}

	};

	int bitmapbuffer_release(lua_State *L)
	{
		LuaKit::ReleaseWrapper<BitmapBufferApiSngl, ReleaseBitmapBuffer>(L, 1);
		return 0;
	}

	int bitmapbuffer_putpixel(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);
		luaL_checktype(L, 3, LUA_TNUMBER);
		luaL_checktype(L, 4, LUA_TNUMBER);
		luaL_checktype(L, 5, LUA_TNUMBER);		
		luaL_checktype(L, 6, LUA_TNUMBER);		

		BitmapBuffer* pBitmapBuffer = LuaKit::PopApiData<BitmapBufferApiSngl>(L, 1);		

		unsigned int x = (unsigned int)lua_tonumber(L, 2);
		unsigned int y = (unsigned int)lua_tonumber(L, 3);

		RgbColor color(
			(unsigned char)lua_tonumber(L, 4),
			(unsigned char)lua_tonumber(L, 5),
			(unsigned char)lua_tonumber(L, 6));

		PutPixel(pBitmapBuffer, x, y, color);

		return 0;
	}

	class BitmapBufferMethods
	{
	public:

		BitmapBufferMethods()
		{
			BitmapBufferApiSngl::Instance().AddGlobal("acquireBitmapBuffer", bitmapbuffer_acquire);

			BitmapBufferApiSngl::Instance().AddMethod("release", bitmapbuffer_release);
			BitmapBufferApiSngl::Instance().AddMethod("putPixel", bitmapbuffer_putpixel);
		}

	};

	BitmapBufferMethods bitmapBufferMethods;

} // namespace Drawing
