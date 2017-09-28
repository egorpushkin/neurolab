#ifndef STACK_H
#define STACK_H

int stack_parsesequence(lua_State *L, const char* sequence, bool firstLevel);
void stack_pushasstring(lua_State *L, int value);

#endif // !STACK_H
