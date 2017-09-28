#ifndef FACTORY_H__MINCOM__COMMONKIT__INCLUDED_
#define FACTORY_H__MINCOM__COMMONKIT__INCLUDED_

template
<
    class AbstractProduct, 
    typename IdentifierType,
    typename ProductCreator = AbstractProduct (*)()
>
class Factory 
{
	struct Exception : public std::exception
	{
		const char* what() const throw() { return "Unknown Type"; }
	}; 

public:
    bool Register(const IdentifierType& id, ProductCreator creator)
    {
        return associations_.insert(
            typename IdToProductMap::value_type(id, creator)).second;
    }
    
    bool Unregister(const IdentifierType& id)
    {
        return associations_.erase(id) == 1;
    }
    
    AbstractProduct CreateObject(const IdentifierType& id)
    {
        typename IdToProductMap::iterator i = associations_.find(id);
        if (i != associations_.end())
        {
            return (i->second)();
        }
		throw Exception();
    }

	void Release()
	{
		associations_.clear();
	}
    
private:
	typedef Loki::AssocVector<IdentifierType, ProductCreator> IdToProductMap;
    IdToProductMap associations_;
};

typedef Factory
<
	typename ICommonPtr, CLSID
>
CommonFactorySpec;

typedef Loki::SingletonHolder
<
	CommonFactorySpec,
	Loki::CreateUsingNew,
	Loki::DeletableSingleton
> 
CommonFactory;

// Default internal creator routine
template
<
	class T
>
ICommonPtr ObjectCreator()
{
	T* object = new T;
	return ICommonPtr(object, IID_ICommon);
}

// Default factory accessor routine
inline CommonFactory::ObjectType& GetCommonFactory()
{
	return CommonFactory::Instance();
}

// Default client creator routine
inline ICommonPtr CreateObject(REFCLSID clsid)
{
	return GetCommonFactory().CreateObject(clsid);
}

#endif // !FACTORY_H__MINCOM__COMMONKIT__INCLUDED_
