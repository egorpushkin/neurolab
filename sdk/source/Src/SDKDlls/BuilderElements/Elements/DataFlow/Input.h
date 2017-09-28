#ifndef INPUT_H__BUILDERELEMENTS__INCLUDED_
#define INPUT_H__BUILDERELEMENTS__INCLUDED_

#include "../../BuilderElements.h"

class CInput
	: public BuilderElementsCommonKit::CCmnElement
	, public BuilderElementsCommonKit::CCmnBuilderElement
	, public BuilderElementsCommonKit::CCmnDataFlow
	, public BuilderElementsCommonKit::CCmnDataConnector
{
public:
	CInput(void);
	virtual ~CInput(void);

	// Custom tools
	void					PostInitialize();

	// IElement declarations section

	// IBuilderElement declarations section

	// IDataFlow declarations section

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

#endif // !INPUT_H__BUILDERELEMENTS__INCLUDED_
