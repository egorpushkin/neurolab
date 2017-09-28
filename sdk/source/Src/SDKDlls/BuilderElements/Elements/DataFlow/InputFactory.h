#ifndef INPUTFACTORY_H__BUILDERELEMENTS__INCLUDED_
#define INPUTFACTORY_H__BUILDERELEMENTS__INCLUDED_

#include "../../BuilderElements.h"

class CInputFactory  
	: public BuilderElementsCommonKit::CCmnElement
	, public BuilderElementsCommonKit::CCmnBuilderElement
	, public BuilderElementsCommonKit::CCmnDataFlow
	, public BuilderElementsCommonKit::CCmnDataConnector
	, public BuilderElementsCommonKit::CCmnLayer
{
public:
	CInputFactory(void);
	virtual ~CInputFactory(void);

	// Custom tools
	void					PostInitialize();	
	virtual void			CustomCreateWeights(uint inputsCount, uint layerDimension);

	// IElement declarations section

	// IBuilderElement declarations section

	// IDataFlow declarations section
	virtual void			FlowData();

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

#endif // !INPUTFACTORY_H__BUILDERELEMENTS__INCLUDED_
