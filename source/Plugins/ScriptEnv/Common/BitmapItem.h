#pragma once

class CBitmapItem :
	public IObject
{
public:
	CBitmapItem()
		: csFileName(_T(""))		
	{	
	}
	CBitmapItem(CString& FileName)
		: csFileName(FileName)
	{	
	}

	void SetFileName(CString& FileName)
	{
		csFileName = FileName;
	}

	CString	GetFileName()
	{
		return csFileName;
	}

	// IObject implementations section
	virtual CString GetClassString()
	{
        return _T("CBitmapItem");
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
	}

private:
	CString			csFileName;
};