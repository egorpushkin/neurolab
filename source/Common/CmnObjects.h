#pragma once

interface IObject
{
	virtual CString			GetClassString() = 0;
	virtual void			QueryInterface(int iIDD, void** ppvObject) = 0;

	virtual ~IObject() {}
};

