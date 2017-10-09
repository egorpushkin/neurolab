#ifndef ITRAINER_H__TRAINERSMANAGER__INCLUDED_
#define ITRAINER_H__TRAINERSMANAGER__INCLUDED_

/**
* ITrainer interface. Defines trainer's core routines.
*
* @version 1.0.1
*/
interface ITrainer : public MinCOM::ICommon
{

	/**
	* Attaches neural network to be trained or used during training.
	*
	* @param clsid Network identifier.
	* @param piNetwork Pointer to network control interface.
	*/
	virtual result AttachNetwork(REFCLSID clsid, NiKit::INetworkProcessor* piNetwork) = 0;

	/**
	* Attaches data object to be used during training.
	*
	* @param clsid Data object identifier.
	* @param piData Pointer to data object control interface.
	*/
	virtual result AttachDataObject(REFCLSID clsid, DpKit::IDataFile* piData) = 0;

	/**
	* Returns trainer common information.
	*
	* @param info Refers to destination structure. Must not be NULL.
	*/
	virtual result GetTrainerInfo(PTRAINER_INFO info) const = 0;

	/**
	* Returns attached network.
	*
	* @param index Specifies index of network to be returned.
	* @return Network control interface if succeeds, otherwise NULL.
	*/
	virtual NiKit::INetworkProcessor* GetNetwork(uint index) = 0;

	/**
	* Returns attached network.
	*
	* @param clsid Specifies identifier of network to be returned.
	* @return Network control interface if succeeds, otherwise NULL.
	*/
	virtual NiKit::INetworkProcessor* GetNetwork(REFCLSID clsid) = 0;
	
	/**
	* Returns attached data object.
	*
	* @param index Specifies index of data object to be returned.
	* @return Data object control interface if succeeds, otherwise NULL.
	*/
	virtual DpKit::IDataFile* GetDataObject(uint index) = 0;

	/**
	* Returns attached data object.
	*
	* @param clsid Specifies clsid of data object to be returned.
	* @return Data object control interface if succeeds, otherwise NULL.
	*/
	virtual DpKit::IDataFile* GetDataObject(REFCLSID clsid) = 0;

	/**
	* Setups trainer object with logging interface.
	*
	* @param piLog Log provider control interface.
	*/
	virtual result SetLogProvider(ILogProvider* piLog) = 0;

	/**
	* Returns provider object associated with trainer.
	*
	* @return Log provider object.
	*/
	virtual ILogProvider* GetLogProvider() = 0;

};

typedef Container::IEnumerator< 
	ITrainer* 
> ITrainersEnum;

typedef Loki::SmartPtr<	
	ITrainersEnum,	
	Loki::COMRefCounted 
> ITrainersEnumPtr;

typedef MinCOM::ComPtr<	ITrainer > ITrainerPtr;
typedef const ITrainerPtr& ITrainerRef;

#endif // !ITRAINER_H__TRAINERSMANAGER__INCLUDED_
