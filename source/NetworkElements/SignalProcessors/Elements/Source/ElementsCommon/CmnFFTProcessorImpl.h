#pragma once

#include "CmnFFTProcessor.h"

class CFFTProcessorControlImpl : public IFFTProcessorControl
{
public:
	CFFTProcessorControlImpl()
		// FFT Direction
		: iTransformDirection(FFTPC_DIRECT_TRANSFORM)
		// FFT Data Model
		, iDataModel(FFTPC_REAL_DATA)
		// Normalization
		, bNormalize(false)
	{
	}

	virtual bool Serialize(CArchive& ar)
	{
		if (ar.IsLoading())
		{
			ar.Read(&iTransformDirection, sizeof(int));
			ar.Read(&iDataModel, sizeof(int));
			ar.Read(&bNormalize, sizeof(bool));
		} else
		{
			ar.Write(&iTransformDirection, sizeof(int));
			ar.Write(&iDataModel, sizeof(int));
			ar.Write(&bNormalize, sizeof(bool));
		}

		return true;
	}

	// FFT Direction
	virtual void SetTransformDirection(int iDirection)
	{
		if (!(iDirection == FFTPC_DIRECT_TRANSFORM || 
			iDirection == FFTPC_INVERSE_TRANSFORM))
			return;

		iTransformDirection	= iDirection;
	}

	virtual int GetTransformDirection()
	{
		return iTransformDirection;
	}

	// FFT Data Model
	virtual void SetFFTDataModel(int iModel)
	{
		if (!(iModel == FFTPC_COMPLEX_DATA || 
			iModel == FFTPC_REAL_DATA))
			return;

		iDataModel	= iModel;
	}	

	virtual int GetFFTDataModel()
	{
		return iDataModel;
	}

	// Normalization
	virtual void SetNormalizationMethod(bool bNorm)
	{
		bNormalize = bNorm;
	}

	virtual bool GetNormalizationMethod()
	{
		return bNormalize;
	}

protected:	
	// FFT Direction
	int						iTransformDirection;

	// FFT Data Model
	int						iDataModel;

	// Normalization
	bool					bNormalize;
};