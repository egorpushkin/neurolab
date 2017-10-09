#ifndef MANAGER_H__DRAWING__LUA_PACKAGE__INCLUDED_
#define MANAGER_H__DRAWING__LUA_PACKAGE__INCLUDED_

namespace Drawing
{

	class Manager
	{
	public:

		Manager(lua_State* L);
		
		DrawingControl::IControlHolderPtr DisplayControl();

		friend DWORD WINAPI ManagerThread(PVOID param);

	private:

		DrawingControl::IControlHolderPtr GetControl();

		void StopWaiting();

	private:

		HANDLE event_;

		lua_State* L_;

		DrawingControl::IControlHolderPtr controlHolder_;

	};

} // namespace Drawing

#endif // !MANAGER_H__DRAWING__LUA_PACKAGE__INCLUDED_
