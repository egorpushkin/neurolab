//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: Connection.h
//	Description: The CConnection declaration file.

#ifndef CONNECTION_H__NETWORKIMPORTING__INCLUDED_
#define CONNECTION_H__NETWORKIMPORTING__INCLUDED_

// Required predeclarations
interface IElement;

// CConnection implementation
class CConnection
	: public IStorageController
{
public:
	CConnection();
	CConnection(uint count);
	virtual ~CConnection();

	// Manage connection state tools
	void					SizeConnection(uint count);

	// IStorageController declarations section
	result					Serialize(FILEDev& fileDev, bool loading);

	// ICommon declarations section
	virtual	ulong			AddRef();
	virtual	ulong			Release();

	virtual String			GetClassString() const;
	virtual result			QueryInterface(REFIID rIID, void** ppObject);

public:
	// Connection Data
	IElement*				piElement_;    
	CConnection*			pOpposite_;

	CDataFactory			weights_;
	CDataFactory			oldWeights_;

	// Data Flow fields
	CDataFactory			data_;
	bool					hasData_;

	// Network training fields
	CDataFactory			deltas_;

	// Required for serialization operations processing
	dword_ptr				prevPtr_;
	dword_ptr				prevOpositePtr_;

private:
	ulong					numRef_;
};

//
// Declaring aditional user types
//

typedef IEnumerator<CConnection*> IConnectionsEnumerator;

typedef IConnectionsEnumerator IConnectionsEnum;

typedef ComPtr<	IConnectionsEnum > IConnectionsEnumPtr;
typedef const IConnectionsEnumPtr& IConnectionsEnumRef;

#endif // !CONNECTION_H__NETWORKIMPORTING__INCLUDED_
