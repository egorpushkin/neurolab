#include "stdafx.h"

#include "../../Common/Includes.h"

#include "Control.h"

#include "../../Manager/Manager.h"

namespace Drawing
{
	
	int control_create(lua_State *L)
	{
		try
		{
			Manager manager(L);
			DrawingControl::IControlHolderPtr controlHolder = manager.DisplayControl();
			if ( !controlHolder )
				return 0;

			LuaKit::PushApiData<ControlApiSngl>(L, GetImpl(controlHolder));

			return 1;
		}
		catch ( ... )
		{
			luaL_error(L, "Failed to initialize and display drawing control");
		}

		return 0;
	}

	int control_close(lua_State *L)
	{
		DrawingControl::IControlHolder* piControlHolder = LuaKit::PopApiData<ControlApiSngl>(L, 1);

		piControlHolder->CloseControl();

		return 0;
	} 

	template
	<
		class T
	>
	class ReleaseControlHolder
	{
	public:

		static void DoRelease(T& ptr)
		{
			if ( ptr )
			{
				ptr->GetDrawingControl()->SetEventsHandler(NULL);
				ptr->Release();
			}
		}

	};

	int control_release(lua_State *L)
	{
		LuaKit::ReleaseWrapper<ControlApiSngl, ReleaseControlHolder>(L, 1);

		return 0;
	}

	int control_setTimer(lua_State *L)
	{
		luaL_checktype(L, 2, LUA_TNUMBER);
		luaL_checktype(L, 3, LUA_TNUMBER);

		DrawingControl::IControlHolder* piControlHolder = LuaKit::PopApiData<ControlApiSngl>(L, 1);

		uint id = (uint)lua_tonumber(L, 2);
		dword elapse = (dword)lua_tonumber(L, 3);		
		
		piControlHolder->GetDrawingControl()->SetTimer(WM_USER + id, elapse);

		return 0;
	} 

	int control_repaint(lua_State *L)
	{
		DrawingControl::IControlHolder* piControlHolder = LuaKit::PopApiData<ControlApiSngl>(L, 1);

		piControlHolder->GetDrawingControl()->Repaint();

		return 0;
	} 

	class ControlMethods
	{
	public:

		ControlMethods()
		{
			ControlApiSngl::Instance().AddGlobal("createControl", control_create);

			// ControlApiSngl::Instance().AddMethod("__gc", control_release);
			ControlApiSngl::Instance().AddMethod("close", control_close);
			
			ControlApiSngl::Instance().AddMethod("setTimer", control_setTimer);
			ControlApiSngl::Instance().AddMethod("repaint", control_repaint);
		}

	};

	ControlMethods controlMethods;

} // namespace LTILib
