#ifndef NEURON_H__BUILDERELEMENTS__INCLUDED_
#define NEURON_H__BUILDERELEMENTS__INCLUDED_

#include "../../BuilderElements.h"

class CNeuron 
	: public BuilderElementsCommonKit::CCmnElement
	, public BuilderElementsCommonKit::CCmnBuilderElement
	, public BuilderElementsCommonKit::CCmnDataFlow
	, public BuilderElementsCommonKit::CCmnDataConnector
{
public:
	CNeuron(void);
	virtual ~CNeuron(void);

	// Custom tools
	void					PostInitialize();

	// IElement declarations section

	// IBuilderElement declarations section

	// IDataFlow declarations section
	virtual void			ProcessElement();

	// IDataConnector declarations section

	// ILayerCOntrol declarations section

	// IStorageController declarations section
	virtual result			Serialize(FILEDev& fileDev, bool loading);

	// ICommon declarations section
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

private:	
	// ICommon members
	ulong					numRef_;
};

#endif // !NEURON_H__BUILDERELEMENTS__INCLUDED_
