#ifndef REFERENCESPOLICY_H__CONTAINER__COMMONKIT__INCLUDED_
#define REFERENCESPOLICY_H__CONTAINER__COMMONKIT__INCLUDED_

template 
<
    class T
>
class WithRefs
{
public:	
    static ulong AddRef(const T& element)  
    {
		ulong refs = 0;
		if (element)
			refs = element->AddRef();
		return refs;
    }

    static ulong Release(const T& element) 
    {
		ulong refs = 0;
		if (element)
			refs = element->Release();
		return refs;
    }
};

template 
<
	class T
>
class MapRefs
{
public:	
	static ulong AddRef(const T& element)  
	{
		return WithRefs< T::second_type >::AddRef(element.second);
	}

	static ulong Release(const T& element) 
	{
		return WithRefs< T::second_type >::Release(element.second);
	}
};

template 
<
    class T
>
class NoRefs
{
public:
    static ulong AddRef(const T& /* element */) 
    {
        return 0;
    }

    static ulong Release(const T& /* element */) 
    {
        return 0;
    }
};

#endif // !REFERENCESPOLICY_H__CONTAINER__COMMONKIT__INCLUDED_
