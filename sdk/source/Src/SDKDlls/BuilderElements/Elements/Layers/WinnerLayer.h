#ifndef WINNERLAYER_H__BUILDERELEMENTS__INCLUDED_
#define WINNERLAYER_H__BUILDERELEMENTS__INCLUDED_

#include "../../BuilderElements.h"

class CWinnerLayer 
	: public BuilderElementsCommonKit::CCmnElement
	, public BuilderElementsCommonKit::CCmnBuilderElement
	, public BuilderElementsCommonKit::CCmnDataFlow
	, public BuilderElementsCommonKit::CCmnDataConnector
	, public BuilderElementsCommonKit::CCmnLayer
{
public:
	CWinnerLayer(void);
	virtual ~CWinnerLayer(void);

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

#endif // !WINNERLAYER_H__BUILDERELEMENTS__INCLUDED_
