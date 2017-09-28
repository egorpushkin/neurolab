#pragma once

// Note:	Enumerators of range 0..5 are used by application
//			Use enumerators from 6 to 9 in plugins and trainers

#define MAX_ENUMERATORS					10

#define USER_ENUMERATOR_RANGE_FROM		6
#define USER_ENUMERATOR_RANGE_TO		9

#define ENUMERATOR(var_list, var_type, func_create, func_next, var_enum)	\
																			\
private:																	\
	POSITION var_enum[MAX_ENUMERATORS];										\
																			\
public:																		\
	virtual bool func_create(int enum_number = 0)							\
	{																		\
		if (enum_number < MAX_ENUMERATORS)									\
		{																	\
			var_enum[enum_number] = var_list.GetHeadPosition();				\
			return true;													\
		}																	\
		return false;														\
	}																		\
																			\
	virtual var_type func_next(int enum_number = 0)							\
	{																		\
		if (enum_number >= MAX_ENUMERATORS)									\
			return NULL;													\
																			\
		if (var_enum[enum_number] == NULL)									\
			return NULL;													\
																			\
		var_type pObject = (var_type)var_list.GetAt(var_enum[enum_number]);	\
		var_list.GetNext(var_enum[enum_number]);							\
		return pObject;														\
	}

#define INTERFACE_ENUMERATOR_DECLARATION(var_type, func_create, func_next)	\
	virtual bool			func_create(int enum_number = 0) = 0;			\
	virtual var_type		func_next(int enum_number = 0) = 0;				

#define RELEASE_LIST(ver_name, var_type, remove_flag)						\
	while (ver_name.GetCount() > 0)											\
	{																		\
		var_type tmItem = ver_name.GetHead();								\
		ver_name.RemoveHead();												\
																			\
		if (remove_flag)													\
			delete tmItem;													\
	}																		
