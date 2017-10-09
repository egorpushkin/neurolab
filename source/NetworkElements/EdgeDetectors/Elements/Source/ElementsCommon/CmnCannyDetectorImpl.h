#pragma once

#include "CmnCannyDetector.h"

class CCmnCannyDetectorImpl : public ICannyDetectorControl
{
public:
	CCmnCannyDetectorImpl()
		// Image Properties
		: iDataImageWidth(64)
		, iDataImageHeight(64)
		// Gaussian Sigma
		, fGaussianSigmaX(3.0f)
		, fGaussianSigmaY(3.0f)
		// Canny Noise
		, fCannyFraction(0.3f)
		, fCannyLowThreshold(2.0f)
		, fCannyHighThreshold(4.0f)    
		// Polygonal Approximation
		, fMinLengthOfSegment(5.0f)
		, fMaxDeviation(1.5f)
	{
	}

	virtual bool Serialize(CArchive& ar)
	{
		if (ar.IsLoading())
		{
			ar.Read(&iDataImageWidth, sizeof(int));
			ar.Read(&iDataImageHeight, sizeof(int));

			ar.Read(&fGaussianSigmaX, sizeof(float));	
			ar.Read(&fGaussianSigmaY, sizeof(float));	
			ar.Read(&fCannyFraction, sizeof(float));	
			ar.Read(&fCannyLowThreshold, sizeof(float));	
			ar.Read(&fCannyHighThreshold, sizeof(float));	
			ar.Read(&fMinLengthOfSegment, sizeof(float));	
			ar.Read(&fMaxDeviation, sizeof(float));	
		} else
		{
			ar.Write(&iDataImageWidth, sizeof(int));
			ar.Write(&iDataImageHeight, sizeof(int));

			ar.Write(&fGaussianSigmaX, sizeof(float));	
			ar.Write(&fGaussianSigmaY, sizeof(float));	
			ar.Write(&fCannyFraction, sizeof(float));	
			ar.Write(&fCannyLowThreshold, sizeof(float));	
			ar.Write(&fCannyHighThreshold, sizeof(float));	
			ar.Write(&fMinLengthOfSegment, sizeof(float));	
			ar.Write(&fMaxDeviation, sizeof(float));	
		}

		return true;
	}

// ICannyDetectorControl implementations section
	// Image Properties
	virtual int	GetDataImageWidth()
	{	
		return iDataImageWidth;
	}

	virtual int	GetDataImageHeight()
	{
		return iDataImageHeight;
	}

	virtual void SetDataImageWidth(int iWidth)
	{
		iDataImageWidth = iWidth;
	}

	virtual void SetDataImageHeight(int iHeight)
	{
		iDataImageHeight = iHeight;
	}

	// Algorithm Parameters
	// Gaussian Sigma
	virtual float GetGaussianSigmaX()
	{
		return fGaussianSigmaX;
	}

	virtual void SetGaussianSigmaX(float fValue)
	{
		fGaussianSigmaX = fValue;
	}

	virtual float GetGaussianSigmaY()
	{
		return fGaussianSigmaY;
	}

	virtual void SetGaussianSigmaY(float fValue)
	{
		fGaussianSigmaY = fValue;
	}
	
	// Canny Noise
	virtual float GetCannyFraction()
	{
		return fCannyFraction;
	}

	virtual void SetCannyFraction(float fValue)
	{
		fCannyFraction = fValue;
	}

	virtual float GetCannyLowThreshold()
	{
		return fCannyLowThreshold;
	}

	virtual void SetCannyLowThreshold(float fValue)
	{
		fCannyLowThreshold = fValue;
	}

	virtual float GetCannyHighThreshold()
	{
		return fCannyHighThreshold;
	}

	virtual void SetCannyHighThreshold(float fValue)
	{
		fCannyHighThreshold = fValue;
	}
	
	// Polygonal Approximation
	virtual float GetMinLengthOfSegment()
	{
		return fMinLengthOfSegment;
	}

	virtual void SetMinLengthOfSegment(float fValue)
	{
		fMinLengthOfSegment = fValue;
	}

	virtual float GetMaxDeviation()
	{
		return fMaxDeviation;
	}

	virtual void SetMaxDeviation(float fValue)
	{
		fMaxDeviation = fValue;
	}

protected:
	// Image Properties
	int						iDataImageWidth;
	int						iDataImageHeight;

	// Algorithm Parameters
	// Gaussian Sigma
	float					fGaussianSigmaX;
	float					fGaussianSigmaY;

	// Canny Noise
	float					fCannyFraction;
	float					fCannyLowThreshold;
	float					fCannyHighThreshold;
    
	// Polygonal Approximation
	float					fMinLengthOfSegment;
	float					fMaxDeviation;
};