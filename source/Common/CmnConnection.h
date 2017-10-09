#pragma once

#include "CmnDataFactory.h"

interface IElement;

class CConnection
{
public:
	CConnection()
	{
		pElement = NULL;
		pOpposite = NULL;

		bHasData = false;
	}

	CConnection(int Count)
	{
		mWeights.CreateFactory(Count);
		mData.CreateFactory(Count);
		mDeltas.CreateFactory(Count);

		pElement = NULL;
		pOpposite = NULL;

		bHasData = false;
	}

	void Serialize(CArchive& ar)
	{	
		if (ar.IsLoading())
		{		
			ar.Read(&pPrevPtr, sizeof(int));			
			ar.Read(&pPrevOpositePtr, sizeof(int));

			ar.Read(&bHasData, sizeof(bool));
		} else
		{		
			CConnection* pThis = this;
			ar.Write(&pThis, sizeof(int));
			ar.Write(&pOpposite, sizeof(int));

			ar.Write(&bHasData, sizeof(bool));		
		}

		mWeights.Serialize(ar);
		mData.Serialize(ar);

		if (ar.IsLoading())
			mDeltas.CreateFactory(mData.GetDataLength());
	}

	void SizeConnection(int Count)
	{
		mWeights.CreateFactory(Count);
		mData.CreateFactory(Count);
		mDeltas.CreateFactory(Count);

		pOpposite->mWeights.CreateFactory(Count);
		pOpposite->mData.CreateFactory(Count);
		pOpposite->mDeltas.CreateFactory(Count);
	}

	// Connection Data
	IElement*				pElement;    
	CConnection*			pOpposite;

	CDataFactory			mWeights;
	CDataFactory			mOldWeights; // requires for training

	// Data Flow fields
	CDataFactory			mData;
	bool					bHasData;

	// Network training fields
	CDataFactory			mDeltas;

	// Required for save/load processing
	CConnection*			pPrevPtr;
	CConnection*			pPrevOpositePtr;
};