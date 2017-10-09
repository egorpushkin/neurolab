#pragma once

#include "interface_idds.h"

#include "CmnObjects.h"
#include "CmnStorage.h"

interface IDataFactory : public IObject
{
	// Creation/Destruction entries
	virtual void			CreateFactory(int DataLength, float InitialData = 0.0f) = 0;
	virtual void			ReleaseFactory() = 0;

	// Data processing routines
	virtual void			SetData(float* pfData, int DataLength) = 0;
	virtual void			SetItemData(int ItemIndex, float Data) = 0;
	virtual void			FillFactory(float Data) = 0;
	virtual void			IncreaseValue(int ItemIndex, float Data) = 0;

	virtual float*			GetData() = 0;
	virtual float*			GetData(int& DataLength) = 0;
	virtual float			GetItemData(int ItemIndex) = 0;
	
	virtual int				GetDataLength() = 0;
};

class CDataFactory : 
	public IDataFactory,
	public IStorageController
{
public:
	CDataFactory() : 
		iDataLength(0),
		pfFactoryData(NULL),
		bFactoryCreated(false)
	{
	}

	CDataFactory(int DataLength) : 
		iDataLength(0),
		pfFactoryData(NULL),
		bFactoryCreated(false)
	{
		CreateFactory(DataLength);
	}

	CDataFactory(int DataLength, float InitialData) :
		iDataLength(0),
		pfFactoryData(NULL),
		bFactoryCreated(false)
	{
		CreateFactory(DataLength, InitialData);
	}

	~CDataFactory()
	{
		if (bFactoryCreated)
			ReleaseFactory();
	}

	// IStorageController implementations section
	virtual bool Serialize(CArchive& ar)
	{
		if (ar.IsLoading())
		{
			ar.Read(&bFactoryCreated, sizeof(bool));

			if (!bFactoryCreated)
				ReleaseFactory();
			else
			{
				int iLength;
				ar.Read(&iLength, sizeof(int));
				
				CreateFactory(iLength);
                ar.Read(pfFactoryData, sizeof(float)*iDataLength);	
			}		
		
		} else
		{
			ar.Write(&bFactoryCreated, sizeof(bool));

			if (bFactoryCreated)
			{
				ar.Write(&iDataLength, sizeof(int));
				ar.Write(pfFactoryData, sizeof(float)*iDataLength);			
			}
		}

		return true;
	}

	// IDataFactory implementations section
	// Creation/Destruction entries
	virtual void CreateFactory(int DataLength, float InitialData = 0.0f)
	{
		if (DataLength <= 0)
			return;

		if (bFactoryCreated)
			ReleaseFactory();
		
		pfFactoryData = new float[DataLength];
		iDataLength = DataLength;

		bFactoryCreated = true;

		FillFactory(InitialData);
	}

	virtual void ReleaseFactory()
	{
		if (pfFactoryData)
			delete []pfFactoryData;

		pfFactoryData = NULL;
		iDataLength = 0;

		bFactoryCreated = false;	
	}

	// Data processing routines
	virtual void SetData(float* pfData, int DataLength)
	{
		if (!bFactoryCreated || DataLength != iDataLength)
			CreateFactory(DataLength);

		memcpy(pfFactoryData, pfData, sizeof(float)*DataLength);
	}

	virtual void SetItemData(int ItemIndex, float Data)
	{
		if (!bFactoryCreated || ItemIndex >= iDataLength)
			return;

        pfFactoryData[ItemIndex] = Data;
	}

	virtual void FillFactory(float Data)
	{
		if (!bFactoryCreated)
			return;

		for(int i = 0;i < iDataLength;i++)
			pfFactoryData[i] = Data;
	}

	virtual void IncreaseValue(int ItemIndex, float Data)
	{
		if (!bFactoryCreated || ItemIndex >= iDataLength)
			return;
	
        pfFactoryData[ItemIndex] += Data;
	}

	virtual float* GetData()
	{
		if (!bFactoryCreated)
			return NULL;

		return pfFactoryData;
	}

	virtual float* GetData(int& DataLength)
	{
		if (!bFactoryCreated)
			return NULL;

		DataLength = iDataLength;
		return pfFactoryData;
	}

	virtual float GetItemData(int ItemIndex)
	{
		if (!bFactoryCreated || ItemIndex >= iDataLength)
			return 0;

		return pfFactoryData[ItemIndex];	
	}
	
	virtual int GetDataLength()
	{
		return iDataLength;	
	}

	// IObject implementations section
	virtual CString GetClassString()
	{
        return _T("CDataFactory");	
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
		switch (iIDD)
		{
		case IDD_IDataFactory:
			*ppvObject = (IDataFactory*)this;
			break;
		case IDD_IStorageController:
			*ppvObject = (IStorageController*)this;
			break;
		}
	}

private:
	int				iDataLength;
	float*			pfFactoryData;

	bool			bFactoryCreated;
};