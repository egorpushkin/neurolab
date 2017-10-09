#pragma once

#include "..\ElementsCommon.h"

#include "ElementsCommon\CmnCannyDetectorImpl.h"

class CCannyDetector :
	public CCmnElement, 
	public CCmnBuilderElement, 
	public CCmnDataFlow, 
	public CCmnDataConnector, 
	public CCmnLayer, 
	public CCmnCannyDetectorImpl, 
	public IStorageController
{
public:
	CCannyDetector(void);
	~CCannyDetector(void);

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

// ILayerControl declarations section
	virtual void			CreateWeights(int Inputs, int Dimension);

// ICannyDetectorControl declarations section

// IStorageController declarations section
	virtual bool			Serialize(CArchive& ar);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	// Canny Detector element UI tools
	void				ShowDataImagePropertiesDlg();
	void				ShowCannyDetectorParametersDlg();

	// Canny Detector element data fields
	int					iImageWidth;
	int					iImageHeight;
};
