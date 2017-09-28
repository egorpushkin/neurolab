#include "stdafx.h"

#include "../Common/Includes.h"

#include "Callback.h"

#include "../API/Control/Control.h"
#include "../API/Graphics/Graphics.h"

namespace Drawing
{

	Callback::Callback(DrawingControl::IControlHolderRef controlHolder, lua_State* L)
		: controlHolder_(controlHolder)
		, L_(L)
		, LChild_(NULL)
	{
		// Check arguments passed to 'DrawingControl::create'
		luaL_checktype(L, 1, LUA_TTABLE);

		// Parse arguments passed to 'DrawingControl::create'
		lua_settop(L_, 1);
		LChild_ = lua_newthread(L_);
		if ( !LChild_ ) 
			luaL_error(L_, "Cannot create new stack");

		// Create a hard reference to the thread object into the registry
		lua_pushlightuserdata(L_, LChild_);
		lua_insert(L_, -2);
		lua_settable(L_, LUA_REGISTRYINDEX);

		// Move args table to child's stack
		lua_xmove(L_, LChild_, 1);
	}

	Callback::~Callback()
	{
	}

	// IEvents section
	void Callback::OnInit()
	{
		// Parse arguments table
		lua_pushstring(LChild_, "oninit");
		lua_gettable(LChild_, -2);  
		if ( !lua_isfunction(LChild_, -1) )
		{
			// luaL_error(LChild_, "Invalid component in callbacks table");
			lua_pop(LChild_, 1);  
			return;
		}

		LuaKit::PushApiData<ControlApiSngl>(LChild_, GetImpl(controlHolder_));

		if ( lua_pcall(LChild_, 1, 0, 0) != 0 )
		{
			// luaL_error(LChild_, "Error running 'onpaint' callback: %s", lua_tostring(LChild_, -1));		
			lua_pop(LChild_, 1);  
			return;			
		}
	}

	void Callback::OnPaint(Gdiplus::Graphics* pGraphics)
	{
		// Parse arguments table
		lua_pushstring(LChild_, "onpaint");
		lua_gettable(LChild_, -2);  
		if ( !lua_isfunction(LChild_, -1) )
		{
			// luaL_error(LChild_, "Invalid component in callbacks table");
			lua_pop(LChild_, 1);  
			return;
		}

		LuaKit::PushApiData<ControlApiSngl>(LChild_, GetImpl(controlHolder_));
		LuaKit::PushApiData<GraphicsApiSngl>(LChild_, pGraphics);
        
		if ( lua_pcall(LChild_, 2, 0, 0) != 0 )
		{
			// luaL_error(LChild_, "Error running 'onpaint' callback: %s", lua_tostring(LChild_, -1));		
			lua_pop(LChild_, 1);  
			return;			
		}
	}

	void Callback::OnTimer(uint nIDEvent)
	{
		// Parse arguments table
		lua_pushstring(LChild_, "ontimer");
		lua_gettable(LChild_, -2);  
		if ( !lua_isfunction(LChild_, -1) )
		{
			// luaL_error(LChild_, "Invalid component in callbacks table");
			lua_pop(LChild_, 1);  
			return;
		}

		LuaKit::PushApiData<ControlApiSngl>(LChild_, GetImpl(controlHolder_));
		lua_pushnumber(LChild_, nIDEvent);

		if ( lua_pcall(LChild_, 2, 0, 0) != 0 )
		{
			// luaL_error(LChild_, "Error running 'onpaint' callback: %s", lua_tostring(LChild_, -1));		
			lua_pop(LChild_, 1);  
			return;			
		}
	}

}
