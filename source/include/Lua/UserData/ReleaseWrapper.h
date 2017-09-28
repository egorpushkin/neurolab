#ifndef RELEASEWRAPPER_H__LUAKIT__INCLUDED_
#define RELEASEWRAPPER_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	template
	<
		class T
	>
	class Release
	{
	public:

		static void DoRelease(T& ptr)
		{
			if ( ptr )
				ptr->Release();
		}

	};

	template
	<
		class T
	>
	class Delete
	{
	public:

		static void DoRelease(T& ptr)
		{
			delete ptr;
		}

	};

	template
	<
		class ApiSnglClass,
		template <class> class ReleaseRule
	> 
	void ReleaseWrapper(
		lua_State* L, 
		int stack = 1)
	{
		try
		{
			LuaKit::DataWrapper< ApiSnglClass::ObjectType::Type_ >* pDataWrapper =	
				(LuaKit::DataWrapper< ApiSnglClass::ObjectType::Type_ >*)							
					auxiliar_checkclass(
						L, 
						ApiSnglClass::Instance().GetClassName(), 
						stack);					

			if ( !pDataWrapper ) 									
			{
				luaL_argerror(L, stack, "Wrong userdata wrapper");	
				throw std::exception("Wrong userdata wrapper");
			}
			
			if ( !pDataWrapper->GetData() )		
			{
				luaL_argerror(L, stack, "Wrong userdata object");	
				throw std::exception("Wrong userdata object");
			}

			// Apply ReleaseRule strategy to deallocate object
			ReleaseRule< ApiSnglClass::ObjectType::Type_ >::
				DoRelease( pDataWrapper->GetData() );

			pDataWrapper->SetData(NULL);	
		}
		catch ( ... )
		{			
		}
	}

} // namespace LuaKit

#endif // !RELEASEWRAPPER_H__LUAKIT__INCLUDED_
