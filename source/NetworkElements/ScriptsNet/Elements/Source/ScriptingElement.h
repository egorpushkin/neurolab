#pragma once

#include "..\ElementsCommon.h"

#include "ScriptingElementCommon\CmnSELayer.h"
#include "ScriptingElementCommon\CmnScriptingElementImpl.h"

class CScriptingElement :
	public CCmnElement, 
	public CCmnBuilderElement, 
	public CCmnDataFlow, 
	public CCmnDataConnector, 
	public CCmnSELayer, 
	public CCmnScriptingElement, 
	public IStorageController
{
public:
	CScriptingElement(void);
	~CScriptingElement(void);

// IElement declarations section
	virtual void			CommandNotify(WPARAM wParam, LPARAM lParam);

// IBuilderElement declarations section
	virtual void			ShowElement();

	virtual bool			IsClicked(CPoint& point);

	virtual CPoint			GetPositionForConnectedElement(CConnection* pConnection);

// IDataFlow declarations section
	virtual void			ProcessElement();
	virtual void			FlowData();

// IDataConnector declarations section

// ILayerCOntrol declarations section

// IScriptingElementControl declarations section
	virtual void			CreateWeightsSE(int Inputs, int Dimension);
	virtual void			RemoveWeightsSE();

// IStorageController declarations section
	virtual bool			Serialize(CArchive& ar);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	// Scripting element UI tools
	void				ShowProcessScriptEditor();
	void				ShowLayerPropertiesDlg();
	void				ShowWeightsMatrixDlg();

	// Scripting element data fields

	int					iImageWidth;
	int					iImageHeight;
};
