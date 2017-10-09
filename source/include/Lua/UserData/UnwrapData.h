#ifndef UNWRAPDATA_H__LUAKIT__INCLUDED_
#define UNWRAPDATA_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	template
	<
		class T
	> 
	T UnwrapData(
		void* pUnknownWrapper)
	{
		try
		{
			DataWrapper<T>* pDataWrapper = 
				static_cast< DataWrapper<T>* >( pUnknownWrapper );
			
            return pDataWrapper->GetData();
		}
		catch ( ... )
		{
			return T();
		}
	}

} // namespace LuaKit

#endif // !UNWRAPDATA_H__LUAKIT__INCLUDED_
