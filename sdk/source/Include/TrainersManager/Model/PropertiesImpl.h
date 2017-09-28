#ifndef PROPERTIESIMPL_H__TRAINERSMANAGER__INCLUDED_
#define PROPERTIESIMPL_H__TRAINERSMANAGER__INCLUDED_

/**
* PropertiesImpl class. Partial IProperties implementation.
*
* @version 1.0.1
*/
class PropertiesImpl 
	: public MinCOM::CommonImpl< IProperties > 
{
public:

	PropertiesImpl()
		: piArguments_(NULL)
	{
		PropertiesContainer* pArguments = new PropertiesContainer;
		pArguments->QueryInterface(Container::IID_IContainer, (void**)&piArguments_);
	}

	virtual ~PropertiesImpl() 
	{
		if (piArguments_)
			piArguments_->Release();
	}

	// IProperties implementations section
	virtual result SetArgument(const StringA& name, const MinCOM::CommonVariant& value) 
	{ 
		return piArguments_->Add(PropertiesPair(name, value));
	}

	virtual result GetArgument(uint index, MinCOM::CommonVariant& value) const 
	{
		if (index >= piArguments_->Size() )
			return S_FALSE;

		value = 
			Container::for_each(
				GetImpl( IPropsEnumPtr( piArguments_->Clone() ) ), 
				Container::IndexLocator< PropertiesPair, Container::NoRefs >(index)
			).GetFoundObject().second;

		return S_OK;
	}

	virtual result GetArgument(const StringA& name, MinCOM::CommonVariant& value) const 
	{ 
		if (piArguments_->Size() == 0)
			return S_FALSE;

		Container::MapByKeyLocator< PropertiesPair, Container::NoRefs > locator(name);

		locator = 
			Container::for_each(
				GetImpl( IPropsEnumPtr( piArguments_->Clone() ) ), 
				locator 
			);

		if (locator.IsFound())
			value = locator.GetFoundObject().second;
        
		return (locator.IsFound() ? S_OK : E_FAIL ); 
	}

	virtual IPropsEnum* GetPropertiesEnum() const 
	{
		return piArguments_->Clone();
	}

	// ICommon implementations section	
	virtual result QueryInterface(REFIID iid, void** ppObject)
	{
		if (iid == MinCOM::IID_ICommon)
			*ppObject = MinCOM::CommonImpl< IProperties >::GetCommon(); 

		else if (iid == IID_IProperties)
			*ppObject = static_cast< IProperties* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		MinCOM::CommonImpl< IProperties >::GetCommon()->AddRef();
		return S_OK;
	}

private:

	IPropertiesContainer* piArguments_;

};

#endif // !PROPERTIESIMPL_H__TRAINERSMANAGER__INCLUDED_
