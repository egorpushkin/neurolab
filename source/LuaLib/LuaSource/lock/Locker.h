#ifndef WIN32_LOCKER_H
#define WIN32_LOCKER_H

void lua_lock(lua_State* L);
void lua_unlock(lua_State* L);
void lua_lockfinal(lua_State* L);

#endif // !WIN32_LOCKER_H
