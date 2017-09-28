#pragma once

#include "..\ElementsCommon.h"

#include "ElementsCommon\CmnFFTProcessorImpl.h"

class CFFTProcessor :
	public CCmnElement, 
	public CCmnBuilderElement, 
	public CCmnDataFlow, 
	public CCmnDataConnector, 
	public CCmnLayer, 
	public CFFTProcessorControlImpl, 
	public IStorageController
{
public:
	CFFTProcessor(void);
	~CFFTProcessor(void);

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

// IFFTProcessorControl declarations section

// IStorageController declarations section
	virtual bool			Serialize(CArchive& ar);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	// FFT Processor element UI tools
	void					ShowPropertiesDlg();

	// Canny Detector element data fields
	int					iImageWidth;
	int					iImageHeight;
};
