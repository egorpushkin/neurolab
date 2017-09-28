#pragma once

#include "CmnObjects.h"

interface ICannyDetectorControl : public IObject
{
	// Image Properties
	virtual int				GetDataImageWidth() = 0;
	virtual void			SetDataImageWidth(int iWidth) = 0;
	
	virtual int				GetDataImageHeight() = 0;	
	virtual void			SetDataImageHeight(int iHeight) = 0;

	// Algorithm Parameters
	// Gaussian Sigma
	virtual float			GetGaussianSigmaX() = 0;
	virtual void			SetGaussianSigmaX(float fValue) = 0;	

	virtual float			GetGaussianSigmaY() = 0;
	virtual void			SetGaussianSigmaY(float fValue) = 0;	
	
	// Canny Noise
	virtual float			GetCannyFraction() = 0;
	virtual void			SetCannyFraction(float fValue) = 0;

	virtual float			GetCannyLowThreshold() = 0;
	virtual void			SetCannyLowThreshold(float fValue) = 0;

	virtual float			GetCannyHighThreshold() = 0;
	virtual void			SetCannyHighThreshold(float fValue) = 0;	
	
	// Polygonal Approximation
	virtual float			GetMinLengthOfSegment() = 0;
	virtual void			SetMinLengthOfSegment(float fValue) = 0;

	virtual float			GetMaxDeviation() = 0;
	virtual void			SetMaxDeviation(float fValue) = 0;

};