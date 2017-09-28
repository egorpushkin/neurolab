#pragma once

#include "..\ElementsCommon.h"

class CInput : 
	public CCmnElement, 
	public CCmnBuilderElement, 
	public CCmnDataFlow, 
	public CCmnDataConnector, 
	public IStorageController
{
public:
	CInput(void);
	~CInput(void);

// IElement declarations section

// IBuilderElement declarations section
	virtual void			ShowElement();

	virtual bool			IsClicked(CPoint& Point);

// IDataFlow declarations section

// IDataConnector declarations section

// IStorageController declarations section
	virtual bool			Serialize(CArchive& ar);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);
};
