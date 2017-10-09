#pragma once

#include "..\Common\LuaDefinitions.h"

#define CHECK_ARGUMENTS_COUNT(number) 								\
	int iNumber = lua_gettop(L);									\
	if (iNumber < number)											\
		return false;											

#define POP_ARGUMENT(type, name, stack_position)					\
	type name =														\
		GetUserDataArgument<type>(L, stack_position, #type);		\
	if (!name)														\
		return false;

#define PUSH_ARGUMENT(type, name, stack_position)					\
	PushDataParameter<type>(L, stack_position, name, #type);

#define POP_ENUMERATOR_INDEX(name, stack_position)					\
	int name = lua_tonumber(L, stack_position);						\
	if (name < USER_ENUMERATOR_RANGE_FROM ||						\
		name > USER_ENUMERATOR_RANGE_TO)							\
		return false;

typedef struct luaL_const {
	const char* name_;
	float value_;
} luaL_const;
