#ifndef CONSTANTINPUT_H__BUILDERELEMENTS__INCLUDED_
#define CONSTANTINPUT_H__BUILDERELEMENTS__INCLUDED_

#include "../../BuilderElements.h"

class CConstantInput 
	: public BuilderElementsCommonKit::CCmnElement
	, public BuilderElementsCommonKit::CCmnBuilderElement
	, public BuilderElementsCommonKit::CCmnDataFlow
	, public BuilderElementsCommonKit::CCmnDataConnector
{
public:
	CConstantInput(void);
	virtual ~CConstantInput(void);

	// Custom tools
	void					PostInitialize();

	// IElement declarations section
	
	// IBuilderElement declarations section

	// IDataFlow declarations section
	virtual bool			RequireData() const;

	// IDataConnector declarations section

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

#endif // !CONSTANTINPUT_H__BUILDERELEMENTS__INCLUDED_
