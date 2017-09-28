#pragma once

class CLayerSerializer
{
public:
	CLayerSerializer()
		: csFileInd("#NL_LAYER_DATA_FILE")
		, csFileVersion("1.0.0.0a")
	{	
	}

// Serialization Tools
	void StoreLayerData(
		ILayerControl* pLayerControl,
		CArchive& ar)
	{
		iLayerDimension = pLayerControl->GetDimension();
		iInputsCount = pLayerControl->GetInputsCount();

		IElement* pElement = NULL;
		pLayerControl->QueryInterface(IDD_IElement, (void**)&pElement);

		csElementName = pElement->GetSysName();
		csElementTitle = pElement->GetElementTitle();
		iElementID = pElement->GetElementID();

		// Serializing file header
		ar.WriteString(csFileInd); ar.Write("\n",1);
		ar.WriteString(csFileVersion); ar.Write("\n",1);

		ar.WriteString(csElementName); ar.Write("\n",1);
		ar.WriteString(csElementTitle); ar.Write("\n",1);
		ar.Write(&iElementID, sizeof(int));

		ar.Write(&iLayerDimension, sizeof(int));
		ar.Write(&iInputsCount, sizeof(int));

		// Serializing layer weights
		for (int i = 0;i < iInputsCount;i++)
			for (int j = 0;j < iLayerDimension;j++)
			{	
				float tmLayerWeight = pLayerControl->GetWeight(i, j);
				ar.Write(&tmLayerWeight, sizeof(float));
			}

		// Serializing layer deltas
		for (int j = 0;j < iLayerDimension;j++)
		{
			float tmLayerDelta = pLayerControl->GetDelta(j);
			ar.Write(&tmLayerDelta, sizeof(float));		
		}

	}

	bool LoadLayerHeader(
		CArchive& ar)
	{
		CString tmFileInd;
		CString	tmFileVersion;

		ar.ReadString(tmFileInd);
		ar.ReadString(tmFileVersion);

		if (tmFileInd != csFileInd || tmFileVersion != csFileVersion)
            return false;

		ar.ReadString(csElementName);
		ar.ReadString(csElementTitle);
		ar.Read(&iElementID, sizeof(int));

		ar.Read(&iLayerDimension, sizeof(int));
		ar.Read(&iInputsCount, sizeof(int));		

		return true;
	}

	bool LoadLayerData(
		ILayerControl* pLayerControl,
		CArchive& ar,
		bool bLoadHeader = false)
	{
		if (bLoadHeader)
		{
			bool bRet = LoadLayerHeader(ar);
            if (!bRet)		
				return false;		
		}

		// Serializing layer weights
		for (int i = 0;i < iInputsCount;i++)
			for (int j = 0;j < iLayerDimension;j++)
			{	
				float tmLayerWeight;
				ar.Read(&tmLayerWeight, sizeof(float));
				
				pLayerControl->SetWeight(i, j, tmLayerWeight);
			}

		// Serializing layer deltas
		for (int j = 0;j < iLayerDimension;j++)
		{
			float tmLayerDelta;
			ar.Read(&tmLayerDelta, sizeof(float));		

			pLayerControl->SetDelta(j, tmLayerDelta);
		}

		return true;
	}

// Data Access Tools
	CString GetElementSysName()
	{
		return csElementName;
	}

	CString GetElementTitle()
	{
		return csElementTitle;
	}

	int GetLayerInputsCount()
	{	
		return iInputsCount;
	}

	int GetLayerDimension()
	{
		return iLayerDimension;	
	}

private:
	CString			csFileInd;
	CString			csFileVersion;

	int				iLayerDimension;
	int				iInputsCount;

	CString			csElementName;
	CString			csElementTitle;
	int				iElementID;
};