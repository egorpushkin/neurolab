#pragma once

class CDataFileItem :
	public IObject
{
public:
	CDataFileItem()
		: csFileName(_T(""))		
	{	
	}
	CDataFileItem(CString& FileName)
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
        return _T("CDataFileItem");
	}

	virtual void QueryInterface(int iIDD, void** ppvObject)
	{
		*ppvObject = NULL;
	}

private:
	CString			csFileName;
};