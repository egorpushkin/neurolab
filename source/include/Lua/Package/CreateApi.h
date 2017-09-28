#ifndef CREATEAPI_H__LUAKIT__INCLUDED_
#define CREATEAPI_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	template 
	<	
		class T,
		class PackageSngl
	> 
	struct CreateApiUsingNew : public Loki::CreateUsingNew<T>
	{
	public:
		static T* Create()
		{ 
			T* object = new T;
			
			PackageSngl::Instance().AddApi(object);
			
			return object; 
		}
	};

} // namespace LuaKit

#endif // !CREATEAPI_H__LUAKIT__INCLUDED_
