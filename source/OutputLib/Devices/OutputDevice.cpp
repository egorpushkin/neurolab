// OutputDevice.cpp : implementation file
//

#include "stdafx.h"
#include "OutputDevice.h"
#include ".\outputdevice.h"

#include "interface_idds.h"

// COutputDevice

IMPLEMENT_DYNAMIC(COutputDevice, CWnd)
COutputDevice::COutputDevice()
{
	pDeviceDriver = NULL;
	pDefaultDeviceFont = NULL;

	iXScrollOffset = 0;
	iYScrollOffset = 0;

	iMaxXScrollPos = 10000;
	iMaxYScrollPos = 10000;
}

COutputDevice::~COutputDevice()
{
	if (pDefaultDeviceFont)
		delete pDefaultDeviceFont;

	if (pDeviceDriver)
		delete pDeviceDriver;

	FreeImagesCollection();
}


BEGIN_MESSAGE_MAP(COutputDevice, CWnd)	
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// Creating and initialization functions
BOOL COutputDevice::CreateDevice(CRect& rect, CWnd * pParentWnd, UINT ctrlId)
{
	BOOL bRet = CWnd::Create(NULL, "", WS_VISIBLE | WS_HSCROLL | WS_VSCROLL, 
		rect, pParentWnd, ctrlId, NULL);

	if (bRet)
	{
		bool bResult = InitializeOpenGL();
		bResult = SetupOpenGL();
	}

	return bRet;
}

void COutputDevice::SetAppFolder(CString& AppFolder)
{
	csAppFolder = AppFolder;
}

// Device Driver processing functions
CDeviceDriver* COutputDevice::CreateDeviceDriver(CDC * pDC)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	CRect rect;
	GetClientRect(&rect);

	glViewport(0, 0, rect.Width(), rect.Height());

	UpdateEnvironmentSettings();

	CDeviceDriver* pDrv = new CDeviceDriver(pDC, rect);
	pDrv->QueryInterface(IDD_IDeviceDriver, (void**)&pDeviceDriver);

	if (!pDefaultDeviceFont)
		CreateDefaultFont(pDC->m_hDC);

	return pDrv;
}

void COutputDevice::ReleaseDeviceDriver(CDeviceDriver * pDrv)
{
	pDrv->SwapBuffers();
	
	delete pDrv;
	pDeviceDriver = NULL;
}

// Setup OpenGl functions 
void COutputDevice::UpdateEnvironmentSettings()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -2.42f);	
}

bool COutputDevice::InitializeOpenGL(void)
{
	if (!m_hWnd)
		return false;

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	
		1,					
		PFD_DRAW_TO_WINDOW|	
		PFD_SUPPORT_OPENGL|	
		PFD_DOUBLEBUFFER,	
		PFD_TYPE_RGBA,		
		32,				
		0, 0, 0, 0, 0, 0,		
		0,				
		0,				
		0,				
		0, 0, 0, 0,		
		32,				
		0,				
		0,				
		PFD_MAIN_PLANE,	
		0,				
		0, 0, 0			
	};

	HDC hDC = ::GetDC(m_hWnd);

	oglPixelFormat = ChoosePixelFormat(hDC, &pfd);

	if(!oglPixelFormat)
		return false;			

	if(!SetPixelFormat(hDC, oglPixelFormat, &pfd)) 
		return false;

	hRC = wglCreateContext(hDC);		
	if(!hRC)
		return false;

	if(!wglMakeCurrent(hDC, hRC)) 
		return false;

	return true;
}

bool COutputDevice::SetupOpenGL(void)
{
	CRect	ClRect;
	GetClientRect(&ClRect);

	glClearColor(0.878f, 0.875f, 0.890f, 0.0f);
	
	glClearDepth(1.0);		
	glDepthFunc(GL_LESS);	
	glEnable(GL_DEPTH_TEST);	

	glShadeModel(GL_SMOOTH);	

	glMatrixMode(GL_PROJECTION);		
	gluPerspective(45.0f, (GLfloat)ClRect.Width() / (GLfloat)ClRect.Height(), 0.1f, 100.0f);	

	glMatrixMode(GL_MODELVIEW);	

	return true;
}

// Text processing functions
void COutputDevice::CreateDefaultFont(HDC hDC)
{
	pDefaultDeviceFont = new CDeviceFont(hDC, 10, 0, 0, 0);
}

// Image processing functions
void COutputDevice::FreeImagesCollection()
{
	for (;mImagesCollection.GetCount() > 0;)
	{
		sDeviceBitmap * pBitmapRec = mImagesCollection.GetHead();
		
		free(pBitmapRec->pImage->data);
		free(pBitmapRec->pImage);
		delete pBitmapRec;

		mImagesCollection.RemoveHead();		
	}
}

// IOutputDevice implementations section
CPoint COutputDevice::TransformPoint(CPoint& Point)
{
	CPoint tmPoint = Point;
	
	tmPoint.Offset(iXScrollOffset, iYScrollOffset);
	tmPoint = pDeviceDriver->TransformPoint(tmPoint);
    
	return tmPoint;
}

IDeviceDriver* COutputDevice::GetDeviceDriver()
{	
	return pDeviceDriver;
}

sDeviceBitmap* COutputDevice::GetImageByName(CString& ImageRecordName)
{
	POSITION pos = mImagesCollection.GetHeadPosition();
	for (;pos;)
	{
		sDeviceBitmap * pBitmapRec = mImagesCollection.GetNext(pos);
		if (pBitmapRec->csImageName == ImageRecordName)
			return pBitmapRec;	
	}

	return NULL;
}

void COutputDevice::LoadImage(CString& FileName, CString& ImageRecordName)
{
	sDeviceBitmap * pBitmapRec = new sDeviceBitmap;
	pBitmapRec->csImageName = ImageRecordName;

	pBitmapRec->pImage = auxDIBImageLoad(csAppFolder + CString("\\") + FileName);

	glNewList(pBitmapRec->iTextureID = glGenLists(1), GL_COMPILE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
		pBitmapRec->pImage->sizeX,
		pBitmapRec->pImage->sizeY,
		0, GL_RGB, GL_UNSIGNED_BYTE,
		pBitmapRec->pImage->data);

	glEndList();

	mImagesCollection.AddTail(pBitmapRec);
}

IDeviceFont* COutputDevice::GetDefaultFont()
{
	IDeviceFont* pDeviceFont = NULL;
	pDefaultDeviceFont->QueryInterface(IDD_IDeviceFont, (void**)&pDeviceFont);

	return pDeviceFont;
}

// IObject implementations section
CString COutputDevice::GetClassString()
{
	return _T("COutputDevice");
}

void COutputDevice::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IOutputDevice:
		*ppvObject = (IOutputDevice*)this;
		break;
	}
}

// COutputDevice message handlers
void COutputDevice::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
   int iCurScrollPos = GetScrollPos(SB_VERT);
    int iOldScrollPos = iCurScrollPos;
    switch (nSBCode)
	{
	case SB_LEFT:
		iCurScrollPos = 0;
		break;
	case SB_LINELEFT:
		iCurScrollPos--;
		break;
	case SB_LINERIGHT:
		iCurScrollPos++;
		break;
	case SB_PAGELEFT:
		iCurScrollPos -= iMaxYScrollPos/160;
		break;
	case SB_PAGERIGHT:
		iCurScrollPos += iMaxYScrollPos/160;
		break;
	case SB_RIGHT:
		iCurScrollPos = iMaxYScrollPos;
		break;
	case SB_THUMBTRACK:
		iCurScrollPos = nPos;
	}
	if (iCurScrollPos < 0)
		iCurScrollPos = 0;
	if (iCurScrollPos > iMaxYScrollPos)
		iCurScrollPos = iMaxYScrollPos;
	
	SetScrollPos(SB_VERT, iCurScrollPos, TRUE);
    iYScrollOffset += -iCurScrollPos + iOldScrollPos;

	Invalidate();

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void COutputDevice::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
    int iCurScrollPos = GetScrollPos(SB_HORZ);
    int iOldScrollPos = iCurScrollPos;
    switch (nSBCode)
	{
	case SB_LEFT:
		iCurScrollPos = 0;
		break;
	case SB_LINELEFT:
		iCurScrollPos--;
		break;
	case SB_LINERIGHT:
		iCurScrollPos++;
		break;
	case SB_PAGELEFT:
		iCurScrollPos -= iMaxXScrollPos/160;
		break;
	case SB_PAGERIGHT:
		iCurScrollPos += iMaxXScrollPos/160;
		break;
	case SB_RIGHT:
		iCurScrollPos = iMaxXScrollPos;
		break;
	case SB_THUMBTRACK:
		iCurScrollPos = nPos;
	}
	if (iCurScrollPos < 0)
		iCurScrollPos = 0;
	if (iCurScrollPos > iMaxXScrollPos)
		iCurScrollPos = iMaxXScrollPos;
	
	SetScrollPos(SB_HORZ, iCurScrollPos, TRUE);
    iXScrollOffset += -iCurScrollPos + iOldScrollPos;

	Invalidate();

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL COutputDevice::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	//ScrollWindow(0, zDelta/40, NULL, NULL);

	int nSBCode = SB_PAGERIGHT;
	if (zDelta > 0)
		nSBCode = SB_PAGELEFT;

	SHORT	sCtrlState = GetKeyState(VK_LCONTROL) | GetKeyState(VK_RCONTROL);
	sCtrlState = sCtrlState>>7;
    
	if (sCtrlState)
		OnHScroll(nSBCode, 0, NULL);
	else
		OnVScroll(nSBCode, 0, NULL);

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}