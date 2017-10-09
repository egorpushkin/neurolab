#ifndef CONSTRUCTTOOL_H__COMMON__INCLUDED_
#define CONSTRUCTTOOL_H__COMMON__INCLUDED_

template
<
	class T,
	class U,
	template <class> class AssertionPolicy = AssertOnError
>
class CConstructTool
{
public:
	static U* ConstructObject(REFIID iid)
	{
		T* pObject = new T;

		U* piInterfaceReference = QueryTool<T, U, AssertionPolicy>::QueryInterface(pObject, iid);

		if (!piInterfaceReference)
			delete pObject;

		return piInterfaceReference;
	}
};

template
<
	class T,
	class U,
	template <class> class AssertionPolicy = AssertOnError
>
class ConstructTool 
	: public CConstructTool<T, U, AssertionPolicy>
{
};

#endif // !CONSTRUCTTOOL_H__COMMON__INCLUDED_
