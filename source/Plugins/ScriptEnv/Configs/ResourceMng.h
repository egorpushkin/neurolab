#pragma once

class CResourceManager
{
public:
	static CString GetResourceString(
		UINT ResuorceID, 
		LPCTSTR GroupName = _T("Configuration"))
	{
		CString csResult;

		LPCTSTR lpszResourceName = MAKEINTRESOURCE(ResuorceID);
		ASSERT(lpszResourceName != NULL);

		HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, GroupName);
		HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, GroupName);
		
		if (hRsrc == NULL)
		{
			ASSERT(FALSE);
		}
		else
		{
			HGLOBAL hGlobal = LoadResource(hInst, hRsrc);

			if (hGlobal == NULL)
			{
				ASSERT(FALSE);
			}
			else
			{
				LPSTR lpszText = (LPSTR)LockResource(hGlobal);

				if (lpszText == NULL)
				{
					ASSERT(FALSE);
				}
				else
				{
					USES_CONVERSION;
					csResult = CString(A2T(lpszText));
				}

				UnlockResource(hGlobal);
				FreeResource(hGlobal);
			}
		}

		return csResult;
	}
};
