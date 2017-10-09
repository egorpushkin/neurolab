#ifndef BASEENUM_H__CONTAINER__COMMONKIT__INCLUDED_
#define BASEENUM_H__CONTAINER__COMMONKIT__INCLUDED_

#include "../Policy/ReferencesPolicy.h"

template 
<
	class T,
	template <class> class ReferencesPolicy = WithRefs
>
class BaseEnum
{
public:
	T GetFoundObject() const
	{
		ReferencesPolicy<T>::AddRef(object_);
		return object_;
	}

	bool IsFound() 
	{
		return found_;
	}

protected:
	BaseEnum()
		: object_()
		, found_(false)
	{
	}

	void SetObject(const T& object)
	{
		object_ = object;
		found_ = true;
	}

	T object_;
	bool found_;
};

template
<
	class T,
	template <class> class ReferencesPolicy = WithRefs
>
class IndexLocator
	: public BaseEnum< T, ReferencesPolicy >
{
	typedef BaseEnum< T, ReferencesPolicy > BaseEnumType;

public:
	IndexLocator(uint index)
		: BaseEnumType()
		, requierdIndex_(index)
		, currentIndex_(0)
	{
	}

	void operator ()(const T argument)
	{
		if (currentIndex_ == requierdIndex_)
			BaseEnumType::SetObject(argument);

		++currentIndex_;
	}

private:
	uint requierdIndex_;
	uint currentIndex_;
};

template
<
	class PairType,
	template <class> class ReferencesPolicy = MapRefs
>
class MapByKeyLocator
	: public BaseEnum< PairType, ReferencesPolicy >
{
	typedef BaseEnum< PairType, ReferencesPolicy > BaseEnumType;
	typedef typename PairType::first_type MapKeyType;

public:
	MapByKeyLocator(MapKeyType key)
		: BaseEnumType()
		, key_(key)
	{
	}

	void operator ()(const PairType mapPair)
	{	
		if (mapPair.first == key_)
			BaseEnumType::SetObject(mapPair);
	}

private:
	MapKeyType key_;
};

#endif // !BASEENUM_H__CONTAINER__COMMONKIT__INCLUDED_
