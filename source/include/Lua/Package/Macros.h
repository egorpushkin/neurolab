#ifndef MACROS_H__PACKAGE__LUAKIT__INCLUDED_
#define MACROS_H__PACKAGE__LUAKIT__INCLUDED_

#define DECLARE_API(api, type, package)								\
	class api##Api : public LuaKit::ApiImpl							\
	{																\
	public:															\
		api##Api();													\
		typedef type PureType_;										\
		typedef type* Type_;										\
	};																\
	template < class T >											\
	struct api##Creator												\
		: public LuaKit::CreateApiUsingNew< T, package >			\
	{};																\
	typedef Loki::SingletonHolder<									\
		api##Api,													\
		api##Creator												\
	> api##ApiSngl;													

#define IMPLEMENT_API(api, name)									\
	api##Api::api##Api()											\
		: LuaKit::ApiImpl()											\
	{																\
		LuaKit::ApiImpl::SetClassName(name);						\
	}	



#endif // !MACROS_H__PACKAGE__LUAKIT__INCLUDED_
