#pragma once

#include "CmnObjects.h"

#define FFTPC_DIRECT_TRANSFORM				1
#define FFTPC_INVERSE_TRANSFORM				-1

#define FFTPC_COMPLEX_DATA					0x0001
#define FFTPC_REAL_DATA						0x0002

interface IFFTProcessorControl : public IObject
{
	// FFT Direction
	virtual void			SetTransformDirection(int iDirection) = 0;
	virtual int				GetTransformDirection() = 0;

	// FFT Data Model
	virtual void			SetFFTDataModel(int iModel) = 0;
	virtual int				GetFFTDataModel() = 0;

	// Normalization
	virtual void			SetNormalizationMethod(bool bNorm) = 0;
	virtual bool			GetNormalizationMethod() = 0;
};