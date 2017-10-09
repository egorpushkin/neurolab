#ifndef GNUCCPP_LOCKER_H
#define GNUCCPP_LOCKER_H

void lua_lock(lua_State* L);
void lua_unlock(lua_State* L);
void lua_lockfinal(lua_State* L);

#endif // !GNUCCPP_LOCKER_H
