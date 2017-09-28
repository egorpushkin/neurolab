#pragma once

#include "CannyAlgorithmSource.h"

class CCannyAlgorithm
{
public:
	void FindEdges(
		IDataFactory*			pSourceDataFactory,
		IDataFactory*			pDestinationDataFactory,
		ICannyDetectorControl*	pCannyDetectorControl)
	{		
		int iImageWidth = pCannyDetectorControl->GetDataImageWidth();
		int iImageHeight = pCannyDetectorControl->GetDataImageHeight();

		if (iImageWidth <= 0 || iImageHeight <= 0)
			return;

		// Configuring detection algorithm
		using namespace lumo_cedges;
		autodel<CEdges> cedges = new CEdges();

		cedges->set_gauss(
			pCannyDetectorControl->GetGaussianSigmaX(),
			pCannyDetectorControl->GetGaussianSigmaY());
		cedges->set_noise(
			pCannyDetectorControl->GetCannyFraction(),
			pCannyDetectorControl->GetCannyLowThreshold(),
			pCannyDetectorControl->GetCannyHighThreshold());
		cedges->set_poly(
			pCannyDetectorControl->GetMinLengthOfSegment(),
			pCannyDetectorControl->GetMaxDeviation());

		// Initializing data image
		ByteArray image(iImageWidth, iImageHeight);
		for (int j = 0;j < iImageHeight;j++)
			for (int i = 0;i < iImageWidth;i++)
				image(i, j) = pSourceDataFactory->GetItemData(j * iImageWidth + i);			

		cedges->set_image(&image(0, 0), iImageWidth, iImageHeight);

		// Processing algorithm
		cedges->compute();

		// Receiving and converting prepared edges map
		ByteArray edges(cedges->dim(0),cedges->dim(1));
		cedges->get_eimage(&edges(0,0),edges.dim(0),edges.dim(1));
		
		for (int j = 0;j < iImageHeight;j++)
			for (int i = 0;i < iImageWidth;i++)			
				pDestinationDataFactory->SetItemData(j * iImageWidth + i, edges(i, j));
	}
};