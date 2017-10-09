//	This code is a part of 'Common SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: CommonImpl.h
//	Description: Implementation of ICommon interface. 
//	Base for AddRef/Release mechanism.

#ifndef COMMONIMPLOLD_H__COMMON__INCLUDED_
#define COMMONIMPLOLD_H__COMMON__INCLUDED_

// CCommonImpl implementation
class CCommonImpl : public ICommon
{
public:
	CCommonImpl()
		: numRef_(0)
	{
	}

	virtual ~CCommonImpl() {}

	// ICommon implementations section
	virtual	ulong AddRef()
	{
		return ++numRef_;						
	}

	virtual	ulong Release()
	{
		--numRef_;

		if (numRef_ == 0)
		{
			delete this;
			return 0;
		}

		return numRef_;
	}

	virtual	String GetClassString() const
	{
		return _T("CCommonImpl");
	}

	virtual result QueryInterface(REFIID rIID, void** ppObject)
	{
		if (rIID == IID_ICommon)
		{		
			*ppObject = (ICommon*)this;
		}
		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		((ICommon*)this)->AddRef();
		return S_OK;
	}

private:
	ulong					numRef_;

};

#endif // !COMMONIMPLOLD_H__COMMON__INCLUDED_
