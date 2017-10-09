#ifndef __BCGCBPRO_H
#define __BCGCBPRO_H

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define _BCGPEDIT_STANDALONE

/*#ifdef _BCGPEDIT_IN_OTHER_DLL
BCGCBPRODLLEXPORT void BCGPEditDllInitialize ();
#endif // _BCGCBPRO_IN_OTHER_DLL*/

#ifdef DLL_CONNECT
	#define BCGCBPRODLLEXPORT __declspec(dllexport)
#else
	#define BCGCBPRODLLEXPORT __declspec(dllimport)
#endif

/*#if defined _AFXDLL && !defined _BCGPEDIT_STATIC_
	#ifdef _BCGPEDIT_
	   #define BCGCBPRODLLEXPORT  __declspec(dllexport)
	#else
	   #define BCGCBPRODLLEXPORT  __declspec(dllimport)
	#endif
#else
	#define BCGCBPRODLLEXPORT
#endif*/

class BCGCBPRODLLEXPORT CBCGPMemDC
{
public:
	static BOOL	m_bUseMemoryDC;

	CBCGPMemDC(CDC& dc, CWnd* pWnd) :
		m_dc (dc),
		m_bMemDC (FALSE),
		m_pOldBmp (NULL)
	{
		ASSERT_VALID(pWnd);

		pWnd->GetClientRect (m_rect);

		m_rect.right += pWnd->GetScrollPos (SB_HORZ);
		m_rect.bottom += pWnd->GetScrollPos (SB_VERT);

		if (m_bUseMemoryDC &&
			m_dcMem.CreateCompatibleDC (&m_dc) &&
			m_bmp.CreateCompatibleBitmap (&m_dc, m_rect.Width (), m_rect.Height ()))
		{
			//-------------------------------------------------------------
			// Off-screen DC successfully created. Better paint to it then!
			//-------------------------------------------------------------
			m_bMemDC = TRUE;
			m_pOldBmp = m_dcMem.SelectObject (&m_bmp);
		}
	}

	virtual ~CBCGPMemDC()
	{
		if (m_bMemDC)
		{
			//--------------------------------------
			// Copy the results to the on-screen DC:
			//-------------------------------------- 
			CRect rectClip;
			int nClipType = m_dc.GetClipBox (rectClip);

			if (nClipType != NULLREGION)
			{
				if (nClipType != SIMPLEREGION)
				{
					rectClip = m_rect;
				}

				m_dc.BitBlt (rectClip.left, rectClip.top, rectClip.Width(), rectClip.Height(),
							   &m_dcMem, rectClip.left, rectClip.top, SRCCOPY);
			}

			m_dcMem.SelectObject (m_pOldBmp);
		}
	}

	CDC& GetDC ()			{	return m_bMemDC ? m_dcMem : m_dc;	}
	BOOL IsMemDC () const	{	return m_bMemDC;	}

protected:
	CDC&		m_dc;
	BOOL		m_bMemDC;
	CDC			m_dcMem;
	CBitmap		m_bmp;
	CBitmap*	m_pOldBmp;
	CRect		m_rect;
};

#if _MSC_VER < 1300

//------------------------------
// Windows 64 bit compatibility:
//------------------------------

#define	DWORD_PTR			DWORD

#endif // _MSC_VER

#endif // __BCGCBPRO_H
