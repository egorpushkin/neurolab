//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IDataFactory.h
//	Description: The IDataFactory declaration file.

#ifndef IDATAFACTORY_H__DATAPROCESSING__INCLUDED_
#define IDATAFACTORY_H__DATAPROCESSING__INCLUDED_

// IDataFactory declaration
interface IDataFactory : public ICommon
{
	// Creation/Destruction functions
	virtual void			CreateFactory(uint DataLength, float InitialData = 0.0f) = 0;
	virtual void			ReleaseFactory() = 0;

	// Data processing functions
	virtual void			SetData(const IDataFactory* piData) = 0;
	virtual void			SetData(const float* pfData, uint DataLength) = 0;
    virtual void			SetItemData(uint ItemIndex, float Data) = 0;
	virtual void			FillFactory(float Data) = 0;
	virtual void			IncreaseValue(uint ItemIndex, float Data) = 0;

	virtual float*			GetData() const = 0;
	virtual float*			GetData(uint& DataLength) const = 0;
	virtual float			GetItemData(uint ItemIndex) const = 0;
	
	virtual uint			GetDataLength() const = 0;
};

typedef ComPtr< IDataFactory > IDataFactoryPtr;

#endif // !IDATAFACTORY_H__DATAPROCESSING__INCLUDED_
