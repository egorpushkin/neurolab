#ifndef CUSTOMFACTORY_H__MINCOM__LOKI__INCLUDED_
#define CUSTOMFACTORY_H__MINCOM__LOKI__INCLUDED_

namespace Loki
{

    template
    <
        class AbstractProduct, 
        typename IdentifierType,
        typename ProductCreator = AbstractProduct (*)()
    >
    class CustomFactory 
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
        
    private:
        typedef AssocVector<IdentifierType, ProductCreator> IdToProductMap;
        IdToProductMap associations_;
    };

}

#endif // !CUSTOMFACTORY_H__MINCOM__LOKI__INCLUDED_
