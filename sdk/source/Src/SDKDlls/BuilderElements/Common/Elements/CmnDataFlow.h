#ifndef CMNDATAFLOW_H__BUILDERELEMENTS__INCLUDED_
#define CMNDATAFLOW_H__BUILDERELEMENTS__INCLUDED_

class CCmnDataFlow 
	: public NetworkImportingKit::IDataFlow
	, public IStorageController
{
public:
	CCmnDataFlow();
	virtual ~CCmnDataFlow();

protected:
	// Custom tools
	bool					GetFactoryReadyState(uint factoryType);

	// IStorageController declarations section
	virtual result			Serialize(FILEDev& fileDev, bool loading);

	// IDataFlow declarations section
	virtual const NetworkImportingKit::TransferFunction*		
		GetElementFunction() const;
	virtual void			SetElementFunction(
		NetworkImportingKit::TransferFunction* pFunction);
	virtual const StringA&	GetFunctionName() const;

	virtual bool			RequireData() const;
	virtual void			SetWaitDataState();

	virtual bool			IsReadyForProcessing();
	virtual void			FlowData();
	virtual void			ProcessElement();

	virtual bool			IsReadyForTraining();
	virtual void			BackFlow();

	virtual void			GetElementData(IDataFactory* piData) const;
	virtual void			SetElementData(const IDataFactory* piData);
	virtual IDataFactory*	GetDataFactory() const;			

	virtual void			MergeConnectionsData(IDataFactory* piData, uint factoryType);

protected:
	NetworkImportingKit::TransferFunction*		pActivateFunction_;	
	StringA					functionName_;

	IDataFactory*			piElementData_;
};

#endif // !CMNDATAFLOW_H__BUILDERELEMENTS__INCLUDED_
