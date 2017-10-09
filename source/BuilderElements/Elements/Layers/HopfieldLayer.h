#pragma once

#include "..\ElementsCommon.h"

class CHopfieldLayer : 
	public CCmnElement, 
	public CCmnBuilderElement, 
	public CCmnDataFlow, 
	public CCmnDataConnector, 
	public CCmnLayerControl, 
	public IStorageController
{
public:
	CHopfieldLayer(void);
	~CHopfieldLayer(void);

// Common functions
	bool				FindInFactoryPosition(CConnection* pConnection, int FactoryType, CPoint& pntPos);

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

// IStorageController declarations section
	virtual bool			Serialize(CArchive& ar);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	int					iImageWidth;
	int					iImageHeight;
};
