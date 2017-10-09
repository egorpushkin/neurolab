//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: DataFactory.h
//	Description: The CDataFactory declaration file.

#ifndef DATAFACTORY_H__DATAPROCESSING__INCLUDED_
#define DATAFACTORY_H__DATAPROCESSING__INCLUDED_

// CDataFile declaration
class CDataFactory 
	: public IDataFactory
	, public IStorageController
{
public:
	CDataFactory();
	CDataFactory(uint DataLength);
	CDataFactory(uint DataLength, float InitialData);
	virtual ~CDataFactory();

	// IDataFactory declarations section
	// Creation/Destruction entries
	virtual void			CreateFactory(uint DataLength, float InitialData = 0.0f);
	virtual void			ReleaseFactory();

	// Data processing routines
	virtual void			SetData(const IDataFactory* piData);
	virtual void			SetData(const float* pfData, uint DataLength);
	virtual void			SetItemData(uint ItemIndex, float Data);
	virtual void			FillFactory(float Data);
	virtual void			IncreaseValue(uint ItemIndex, float Data);

	virtual float*			GetData() const;
	virtual float*			GetData(uint& DataLength) const;
	virtual float			GetItemData(uint ItemIndex) const;

	virtual uint			GetDataLength() const;

	// IStorageController declarations section
	virtual result			Serialize(FILEDev& FileDev, bool Loading);

	// IObject declarations section
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID refIID, void** ppvObject);

protected:
	uint					iDataLength;
	float*					pfFactoryData;

	bool					bFactoryCreated;

private:
	ulong					numRef_;
};

#endif // !DATAFACTORY_H__DATAPROCESSING__INCLUDED_
