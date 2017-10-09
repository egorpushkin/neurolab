#ifndef MACROS_H__LTILIB__LUA_PACKAGE__INCLUDED_
#define MACROS_H__LTILIB__LUA_PACKAGE__INCLUDED_

#define SETUP_PARAM(type, obj, param, value)						\
	{																\
		type::parameters obj##params = obj->getParameters();		\
		obj##params.param = value;									\
		obj->setParameters(obj##params);							\
	}

#define IMPLEMENT_SETPARAM_FUNC(name, sngl, param_type, param_name)	\
	int name(lua_State *L)											\
	{																\
		luaL_checktype(L, 2, LUA_TNUMBER);							\
		sngl::ObjectType::Type_ pObject =							\
			LuaKit::PopApiData<sngl>(L, 1);							\
		param_type param_name = (param_type)lua_tonumber(L, 2);		\
		SETUP_PARAM(sngl::ObjectType::PureType_,					\
			pObject, param_name, param_name);						\
		return 0;													\
	}									

#define IMPLEMENT_FACTORY_API(cr_name, rel_name, cr_api_name, sngl, init_class)	\
	int cr_name(lua_State *L)										\
	{																\
		sngl::ObjectType::Type_ pObject =							\
			new sngl::ObjectType::PureType_;						\
		LuaKit::PushApiData<sngl>(L, pObject);						\
		return 1;													\
	}																\
	int rel_name(lua_State *L)										\
	{																\
		LuaKit::ReleaseWrapper<sngl, LuaKit::Delete>(L, 1);			\
		return 0;													\
	}																\
	class init_class												\
	{																\
	public:															\
		init_class()												\
		{															\
			sngl::Instance().AddGlobal(cr_api_name, cr_name);		\
			sngl::Instance().AddMethod("__gc", rel_name);			\
		}															\
	};																\
	init_class init_class##_Instance;

#define IMPLEMENT_FACTORY_API2(api_name, cr_api_name)				\
	int api_name##_create(lua_State *L)								\
	{																\
		api_name##ApiSngl::ObjectType::Type_ pObject =				\
			new api_name##ApiSngl::ObjectType::PureType_;			\
		LuaKit::PushApiData<api_name##ApiSngl>(L, pObject);			\
		return 1;													\
	}																\
	int api_name##_release(lua_State *L)							\
	{																\
		LuaKit::ReleaseWrapper<api_name##ApiSngl, LuaKit::Delete>(L, 1);		\
		return 0;													\
	}																\
	class api_name##Fact											\
	{																\
	public:															\
		api_name##Fact()											\
		{															\
			api_name##ApiSngl::Instance().							\
				AddGlobal(cr_api_name, api_name##_create);			\
			api_name##ApiSngl::Instance().							\
				AddMethod("__gc", api_name##_release);				\
		}															\
	};																\
	api_name##Fact api_name##Fact##_Instance;

#define IMPLEMENT_TRAIN_API(tr_name, sngl, init_class)				\
	int tr_name(lua_State *L)										\
	{																\
		CHECK_PARAMETERS(3);										\
		sngl::ObjectType::Type_ pObject = LuaKit::PopApiData<sngl>(L, 1);	\
		lti::dmatrix* pMatrix = LuaKit::PopApiData<DMatrixApiSngl>(L, 2);	\
		lti::ivector* pVector = LuaKit::PopApiData<IVectorApiSngl>(L, 3);	\
		pObject->train(*pMatrix, *pVector);							\
		return 0;													\
	}																\
	class init_class												\
	{																\
	public:															\
		init_class()												\
		{															\
			sngl::Instance().AddMethod("train", tr_name);			\
		}															\
	};																\
	init_class init_class##_Instance;

#define IMPLEMENT_TRAIN_API2(api_name)								\
	int api_name##_train(lua_State *L)								\
	{																\
		CHECK_PARAMETERS(3);										\
		api_name##ApiSngl::ObjectType::Type_ pObject =				\
			LuaKit::PopApiData<api_name##ApiSngl>(L, 1);			\
		lti::dmatrix* pMatrix = LuaKit::PopApiData<DMatrixApiSngl>(L, 2);	\
		lti::ivector* pVector = LuaKit::PopApiData<IVectorApiSngl>(L, 3);	\
		pObject->train(*pMatrix, *pVector);							\
		return 0;													\
	}																\
	class api_name##Train											\
	{																\
	public:															\
		api_name##Train()											\
		{															\
			api_name##ApiSngl::Instance().							\
				AddMethod("train", api_name##_train);				\
		}															\
	};																\
	api_name##Train api_name##Train##_Instance;

#endif // !MACROS_H__LTILIB__LUA_PACKAGE__INCLUDED_
