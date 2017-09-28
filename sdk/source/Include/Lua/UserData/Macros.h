#ifndef MACROS_H__UDATA__LUAKIT__INCLUDED_
#define MACROS_H__UDATA__LUAKIT__INCLUDED_

#define PUSH_ARGUMENT(type, data, stack)							\
	LuaKit::PushUserData< type >(L, stack, data, #type);

#define POP_ARGUMENT(type, data, stack)								\
	type data =	LuaKit::PopUserData< type >(L, stack, #type);						

#define PUSH_AUXILIAR(type, data, typeId, stack)					\
	LuaKit::CreateUserData< type >(L, data);						\
	auxiliar_setclass(L, typeId, stack); 

#define POP_AUXILIAR(type, data, typeId, stack)						\
	LuaKit::DataWrapper< type >* pDataWrapper##_##data =			\
		(LuaKit::DataWrapper< type >*)								\
			auxiliar_checkclass(L, typeId, stack);					\
	if ( !pDataWrapper##_##data ) 									\
		return luaL_argerror(L, stack, "Wrong userdata wrapper");	\
	if ( !pDataWrapper##_##data->GetData() )						\
		return luaL_argerror(L, stack, "Wrong userdata object");	\
	type data = pDataWrapper##_##data->GetData();			

#define COM_RELEASE_WRAPPER(data)									\
	ulong refs = data->Release();									\
	if ( !refs )													\
		pDataWrapper##_##data->SetData(NULL);	

#define RELEASE_WRAPPER(data)										\
	delete data;													\
	pDataWrapper##_##data->SetData(NULL);		

#define CHECK_PARAMETERS(num)										\
	if ( LuaKit::GetParamsCount(L) < num )							\
		return luaL_error(L, "Wrong number of input parameters");

#define CHECK_PARAMETERS_STRICT(num)								\
	if ( LuaKit::GetParamsCount(L) != num )							\
		return luaL_error(L, "Wrong number of input parameters");



	

#endif // !MACROS_H__UDATA__LUAKIT__INCLUDED_
