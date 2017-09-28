#ifndef TRAINERIMPL_H__TRAINERSMANAGER__INCLUDED_
#define TRAINERIMPL_H__TRAINERSMANAGER__INCLUDED_

/**
* TrainerImpl class. Partial ITrainer implementation.
*
* @version 1.0.1
*/
class TrainerImpl 
	: public MinCOM::CommonImpl< ITrainer > 
{
public:

	TrainerImpl()
		: piLogProvider_(NULL)
		, piNetworks_(NULL)
		, piDataObjects_(NULL)
	{
		NetworksContainer* pNetworks = new NetworksContainer;
		pNetworks->QueryInterface(Container::IID_IContainer, (void**)&piNetworks_);

		DataObjectsContainer* pDataObjects = new DataObjectsContainer;
		pDataObjects->QueryInterface(Container::IID_IContainer, (void**)&piDataObjects_);
	}

	virtual ~TrainerImpl() 
	{
		if (piLogProvider_)
			piLogProvider_->Release();

		if (piNetworks_)
			piNetworks_->Release();

		if (piDataObjects_)
			piDataObjects_->Release();
	}

	// ITrainer implementations section		
	virtual result AttachNetwork(REFCLSID clsid, NiKit::INetworkProcessor* piNetwork)
	{
		return piNetworks_->Add(NetworkPair(clsid, piNetwork));
	}

	virtual result AttachDataObject(REFCLSID clsid, DpKit::IDataFile* piData)
	{
		return piDataObjects_->Add(DataObjectPair(clsid, piData));
	}

	// Not overridden in this scope
	// virtual result GetTrainerInfo(PTRAINER_INFO info) const = 0;

	virtual NiKit::INetworkProcessor* GetNetwork(uint index)
	{
		if (index >= piNetworks_->Size() )
			return NULL;

		return
			Container::for_each(
				GetImpl( INetworksEnumPtr( piNetworks_->Clone() ) ), 
				Container::IndexLocator< NetworkPair, Container::MapRefs >(index)
			).GetFoundObject().second;
	}

	virtual NiKit::INetworkProcessor* GetNetwork(REFCLSID clsid)
	{
		return
			Container::for_each(
				GetImpl( INetworksEnumPtr( piNetworks_->Clone() ) ), 
				Container::MapByKeyLocator< NetworkPair >(clsid)
			).GetFoundObject().second;
	}
	
	virtual DpKit::IDataFile* GetDataObject(uint index)
	{
		if (index >= piDataObjects_->Size() )
			return NULL;

		return
			Container::for_each(
				GetImpl( IDataObjectsEnumPtr( piDataObjects_->Clone() ) ), 
				Container::IndexLocator< DataObjectPair, Container::MapRefs >(index)
			).GetFoundObject().second;
	}

	virtual DpKit::IDataFile* GetDataObject(REFCLSID clsid)
	{
		return
			Container::for_each(
				GetImpl( IDataObjectsEnumPtr( piDataObjects_->Clone() ) ), 
				Container::MapByKeyLocator< DataObjectPair >(clsid)
			).GetFoundObject().second;
	}

	virtual result SetLogProvider(ILogProvider* piLog)
	{
		if (piLogProvider_)
			piLogProvider_->Release();

		piLogProvider_ = piLog;

		if (piLogProvider_)
			piLogProvider_->AddRef();

		return S_OK;
	}

	virtual ILogProvider* GetLogProvider()
	{
		if (piLogProvider_)
			piLogProvider_->AddRef();

		return piLogProvider_;
	}

	// ICommon implementations section	
	virtual result QueryInterface(REFIID iid, void** ppObject)
	{
		if (iid == MinCOM::IID_ICommon)
			*ppObject = MinCOM::CommonImpl< ITrainer >::GetCommon(); 

		else if (iid == IID_ITrainer)
			*ppObject = static_cast< ITrainer* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		MinCOM::CommonImpl< ITrainer >::GetCommon()->AddRef();
		return S_OK;
	}

private:
	ILogProvider* piLogProvider_;

	INetworksContainer* piNetworks_;
	IDataObjectsContainer* piDataObjects_;

};

#endif // !TRAINERIMPL_H__TRAINERSMANAGER__INCLUDED_
