#pragma once

#include "..\ElementsCommon.h"

class CConstantInput : 
	public CCmnElement, 
	public CCmnBuilderElement, 
	public CCmnDataFlow, 
	public CCmnDataConnector, 
	public IStorageController
{
public:
	CConstantInput(void);
	~CConstantInput(void);

// Custom functions
	void				ShowPropertiesDlg();

// IElement declarations section
	virtual void			CommandNotify(WPARAM wParam, LPARAM lParam);

// IBuilderElement declarations section
	virtual void			ShowElement();

	virtual bool			IsClicked(CPoint& Point);

// IDataFlow declarations section
	virtual bool			RequireData();

// IDataConnector declarations section

// IStorageController declarations section
	virtual bool			Serialize(CArchive& ar);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);
};
