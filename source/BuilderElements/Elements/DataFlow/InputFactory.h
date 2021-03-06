#pragma once

#include "..\ElementsCommon.h"

class CInputFactory : 
	public CCmnElement, 
	public CCmnBuilderElement, 
	public CCmnDataFlow, 
	public CCmnDataConnector, 
	public CCmnLayerControl, 
	public IStorageController
{
public:
	CInputFactory(void);
	~CInputFactory(void);

// IElement declarations section
	virtual void			CommandNotify(WPARAM wParam, LPARAM lParam);

// IBuilderElement declarations section
	virtual void			ShowElement();

	virtual bool			IsClicked(CPoint& point);

	virtual CPoint			GetPositionForConnectedElement(CConnection* pConnection);

// IDataFlow declarations section
	virtual void			FlowData();

// IDataConnector declarations section

// ILayerCOntrol declarations section
	virtual void			CreateWeights(int Inputs, int Dimension);

// IStorageController declarations section
	virtual bool			Serialize(CArchive& ar);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	int					iImageWidth;
	int					iImageHeight;
};
