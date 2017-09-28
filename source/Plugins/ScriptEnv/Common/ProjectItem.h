#pragma once

class CProjectItem :
	public IObject
{
public:
	CProjectItem()
		: csFileName(_T(""))		
	{	
	}
	CProjectItem(CString& FileName)
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
        return _T("CProjectItem");
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
	}

private:
	CString			csFileName;
};