#ifndef DATAWRAPPER_H__LUAKIT__INCLUDED_
#define DATAWRAPPER_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	class CommonWrapper {};

	template
	<
		class T
	> 
	class DataWrapper : public CommonWrapper
	{

		DataWrapper(const DataWrapper&);
		const DataWrapper& operator =(const DataWrapper&);

	public:

		DataWrapper()
		{}

		void SetData(T data)
		{
			data_ = data;
		}

		T& GetData()
		{
			return data_;
		}

	private:

		T data_;

	};

} // namespace LuaKit

#endif // !DATAWRAPPER_H__LUAKIT__INCLUDED_
