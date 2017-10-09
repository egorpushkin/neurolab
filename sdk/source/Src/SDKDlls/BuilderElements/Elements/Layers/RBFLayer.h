#ifndef RBFLAYER_H__BUILDERELEMENTS__INCLUDED_
#define RBFLAYER_H__BUILDERELEMENTS__INCLUDED_

#include "../../BuilderElements.h"

class CRBFLayer 
	: public BuilderElementsCommonKit::CCmnElement
	, public BuilderElementsCommonKit::CCmnBuilderElement
	, public BuilderElementsCommonKit::CCmnDataFlow
	, public BuilderElementsCommonKit::CCmnDataConnector
	, public BuilderElementsCommonKit::CCmnLayer
{
public:
	CRBFLayer(void);
	virtual ~CRBFLayer(void);

	// Custom tools
	void					PostInitialize();

	// IElement declarations section

	// IBuilderElement declarations section

	// IDataFlow declarations section
	virtual void			ProcessElement();
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

#endif // !RBFLAYER_H__BUILDERELEMENTS__INCLUDED_
