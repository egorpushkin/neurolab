//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IDataFile.h
//	Description: The IDataFile declaration file.

#ifndef IDATAFILE_H__DATAPROCESSING__INCLUDED_
#define IDATAFILE_H__DATAPROCESSING__INCLUDED_

// IDataFile declaration
interface IDataFile : public ICommon
{
	// Creation/Destruction functions
	virtual void			CreateNewFile(uint InputLength, uint OutputLength) = 0; 
	virtual void			FreeLoadedData() = 0;

	// Save/Load Functions 
	virtual result			LoadFile(LPCSTR FileName) = 0;
	virtual result			SaveToFile(LPCSTR FileName) = 0;

	// Data processing functions
	virtual bool			IsLoaded() = 0;

	virtual uint			GetInputSymbolsCount() = 0;
	virtual uint			GetOutputSymbolsCount() = 0;

	virtual uint			GetInputSymbolLength() = 0;
	virtual uint			GetOutputSymbolLength() = 0;

	virtual IDataFactory*	GetInputSymbol(uint Index) = 0;
	virtual IDataFactory*	GetOutputSymbol(uint Index) = 0;

	virtual void			AddInputSymbol(float Value) = 0;
	virtual void			AddOutputSymbol(float Value) = 0;

	virtual void			AddInputSymbol(IDataFactory* pFactory) = 0;
	virtual void			AddOutputSymbol(IDataFactory* pFactory) = 0;

	virtual void			RemoveInputSymbol(uint Index) = 0;
	virtual void			RemoveOutputSymbol(uint Index) = 0;
};

typedef ComPtr< IDataFile > IDataFilePtr;
typedef const IDataFilePtr& IDataFileRef;

#endif // !IDATAFILE_H__DATAPROCESSING__INCLUDED_
