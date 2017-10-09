#pragma once

#include "CmnLayer.h"

#include "../Resource.h"
#include "Layers\LayerPropertiesDlg.h"

#define LC_TOP_ENUM		2

class CCmnLayerControl : public CCmnLayer
{
public:

	virtual void ShowLayerPropertiesDlg()
	{
		IElement* pElement = NULL;
		QueryInterface(IDD_IElement, (void**)&pElement);

		CLayerPropertiesDlg	mDlg;
		mDlg.SetElement(pElement);
		int iRes = mDlg.DoModal();
		if (iRes == IDOK)
		{
			if (GetDimension() != mDlg.mLayerDimension || 
				GetInputsCount() != mDlg.mInputsCount)
				CreateWeights(mDlg.mInputsCount, mDlg.mLayerDimension);
		}
	}

};