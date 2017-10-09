//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: DataFile.h
//	Description: The CDataFile declaration file.

#ifndef DATAFILE_H__DATAPROCESSING__INCLUDED_
#define DATAFILE_H__DATAPROCESSING__INCLUDED_

// CDataFile declaration
class CDataFile
	: public IDataFile
	, public IStorageController
{
public:
	CDataFile();
	CDataFile(LPCSTR FileName);

	virtual ~CDataFile();

	// IDataFactory declarations section
	// Creation/Destruction functions
	virtual void			CreateNewFile(uint InputLength, uint OutputLength); 
	virtual void			FreeLoadedData();

	// Save/Load Functions 
	virtual result			LoadFile(LPCSTR FileName);
	virtual result			SaveToFile(LPCSTR FileName);

	// Data processing functions
	virtual bool			IsLoaded();

	virtual uint			GetInputSymbolsCount();
	virtual uint			GetOutputSymbolsCount();

	virtual uint			GetInputSymbolLength();
	virtual uint			GetOutputSymbolLength();

	virtual IDataFactory*	GetInputSymbol(uint Index);
	virtual IDataFactory*	GetOutputSymbol(uint Index);

	virtual void			AddInputSymbol(float Value);
	virtual void			AddOutputSymbol(float Value);

	virtual void			AddInputSymbol(IDataFactory* pFactory);
	virtual void			AddOutputSymbol(IDataFactory* pFactory);

	virtual void			RemoveInputSymbol(uint Index);
	virtual void			RemoveOutputSymbol(uint Index);

	// IStorageController declarations section
	virtual result			Serialize(FILEDev& FileDev, bool Loading);

	// IObject declarations section
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID refIID, void** ppvObject);

private:
	bool					bIsFileLoaded;
	
	uint					iInputSymbolsCount;
	uint					iInputSymbolLength;
	uint					iOutputSymbolsCount;
	uint					iOutputSymbolLength;

	CDataFactory**			pInputSymbolsData;
	CDataFactory**			pOutputSymbolsData;

	ulong					numRef_;
};

#endif // !DATAFILE_H__DATAPROCESSING__INCLUDED_
