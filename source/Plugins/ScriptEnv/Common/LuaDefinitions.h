#pragma once

#define lua_userdata_cast(L, pos, T) reinterpret_cast<T>(luaL_checkudata((L), (pos), #T))

// Wrapper for user data objects
template<typename T> 
class CLuaWrapper_UserPointer
{
public:
	template<typename T> CLuaWrapper_UserPointer(T UserData)
		: pUserDataPointer(UserData)
	{}
	T			pUserDataPointer;
};

// Creating wrapped user data and pushing data pointer to Lua stack
template<typename T> 
CLuaWrapper_UserPointer<T>* CreateUserData(lua_State* L, T pDataToBind)
{
	CLuaWrapper_UserPointer<T>* pUserData = 
		(CLuaWrapper_UserPointer<T>*) 
			lua_newuserdata(L, sizeof(CLuaWrapper_UserPointer<T>));
	pUserData->pUserDataPointer = pDataToBind;

	return pUserData;
}

// Receiving user data from created wrapper
template<typename T> 
T GetUserDataFromWrapper(void* pvWrapperData)
{
	CLuaWrapper_UserPointer<T>* pWrapperObject = 
		(CLuaWrapper_UserPointer<T>*) pvWrapperData;

	return pWrapperObject->pUserDataPointer;
}

// Returning user data parameter
template<typename T>
CLuaWrapper_UserPointer<T>* PushDataParameter(lua_State *L, int iMetatablePosition, 
	T UserData, char* pszTypeName)
{
	CLuaWrapper_UserPointer<T>* pUserDataWrapper = CreateUserData<T>(L, UserData);
    luaL_newmetatable(L, pszTypeName);
	lua_setmetatable(L, iMetatablePosition);

	return pUserDataWrapper;
}

// Receiving user data parameter
template<typename T>
T GetUserDataArgument(lua_State *L, int iStackPosition, char* pszTypeName)
{
	if (lua_type(L, iStackPosition) != LUA_TUSERDATA)
		return NULL;

	void* pvUserData = luaL_checkudata(L, iStackPosition, pszTypeName);
	if(!pvUserData)
		return NULL;

	T pData = GetUserDataFromWrapper<T>(pvUserData);

	return pData;
}