//	This code is a part of 'Console Helpers Kit' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: Exceptions.h
//	Description: Exception helper for simple console applications.  

#ifndef EXCEPTIONS_H__CONSOLEHELPERSKIT__INCLUDED_
#define EXCEPTIONS_H__CONSOLEHELPERSKIT__INCLUDED_

// Exception classes
//////////////////////////////////////////////////////////////////////////

// {4c918017-75d1-4a10-ae52-ad87fbdcdc20} 
DEFINE_GUID(CLSID_ConsoleException, 
0x4c918017, 0x75d1, 0x4a10, 0xae, 0x52, 0xad, 0x87, 0xfb, 0xdc, 0xdc, 0x20);

// Exception error codes
//////////////////////////////////////////////////////////////////////////

// ConsoleException declaration
class ConsoleException
	: public exception
{
public:
	ConsoleException()
		: exception()
		, message_(NULL)
		, resultCode_(E_FAIL)
		, clsid_(CLSID_ConsoleException)
	{
	}
	ConsoleException(const char * const& message)
		: exception()
		, message_(message)
		, resultCode_(E_FAIL)        
		, clsid_(CLSID_ConsoleException)
	{
	}
	ConsoleException(const char * const& message, result resultCode)
		: exception()
		, message_(message)
		, resultCode_(resultCode)        
		, clsid_(CLSID_ConsoleException)
	{
	}
	ConsoleException(const char * const& message, result resultCode, REFCLSID clsid)
		: exception()
		, message_(message)
		, resultCode_(resultCode)    
		, clsid_(clsid)
	{
	}
	virtual ~ConsoleException() throw()
	{
	}
	ConsoleException(const ConsoleException& ex)
		: exception()
		, message_(ex.what())
		, resultCode_(ex.GetCode())    
		, clsid_(ex.GetClass())
	{
	}
	const ConsoleException& operator =(const ConsoleException& ex)
	{
		message_ = ex.what();
		resultCode_ = ex.GetCode();
		clsid_ = ex.GetClass();

		return (*this);
	}

	result GetCode() const
	{
		return resultCode_;
	}

	REFCLSID GetClass() const
	{
		return clsid_;
	}

	virtual const char* what() const throw()
	{
		if (!message_)
			return "";
		return message_;
	}

protected:
	const char*				message_;
	result					resultCode_;
	CLSID					clsid_;
};

#endif // !EXCEPTIONS_H__CONSOLEHELPERSKIT__INCLUDED_
