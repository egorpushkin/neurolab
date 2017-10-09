#pragma once

#include "..\ElementsCommon.h"

#include "CmnPCATransform.h"

class CPCATranform :
	public CCmnElement, 
	public CCmnBuilderElement, 
	public CCmnDataFlow, 
	public CCmnDataConnector, 
	public CCmnLayer, 
	public IPCATransform,
	public IStorageController
{
public:
	CPCATranform(void);
	~CPCATranform(void);

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
	virtual bool			ModifyWeights();

// IPCATransform declarations section

// IStorageController declarations section
	virtual bool			Serialize(CArchive& ar);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	// Private UI tools
	void				ShowLayerPropertiesDlg();

private:
	int					iImageWidth;
	int					iImageHeight;
};
