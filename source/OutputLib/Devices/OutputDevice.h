#pragma once

// COutputDevice

#include "DeviceDriver.h"

#include "CmnOutput.h"

class DLL_FUNC_DECLARE CWnd; 
class DLL_FUNC_DECLARE CObject;
//class DLL_FUNC_DECLARE CList;

class DLL_FUNC_DECLARE COutputDevice : 
	public CWnd, 
	public IOutputDevice
{
	DECLARE_DYNAMIC(COutputDevice)

public:
	COutputDevice();
	virtual ~COutputDevice();

	// Creating and initialization functions
	BOOL			CreateDevice(CRect& rect, CWnd * pParentWnd, UINT ctrlId);
	void			SetAppFolder(CString& AppFolder);

	// Device Driver processing functions
	CDeviceDriver*	CreateDeviceDriver(CDC * pDC);
	void			ReleaseDeviceDriver(CDeviceDriver * pDrv);

	// Setup OpenGl functions 
	void			UpdateEnvironmentSettings();
	bool			InitializeOpenGL(void);
	bool			SetupOpenGL(void);

	// Text processing functions
	void			CreateDefaultFont(HDC hDC);

	// Image processing functions
	void			FreeImagesCollection();

// IOutputDevice declarations section
public:
	virtual CPoint			TransformPoint(CPoint& Point);

	virtual IDeviceDriver*	GetDeviceDriver();
	virtual sDeviceBitmap*	GetImageByName(CString& ImageRecordName);     

	virtual void			LoadImage(CString& FileName, CString& ImageRecordName);

	virtual IDeviceFont*	GetDefaultFont();

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:	
	IDeviceDriver*	pDeviceDriver;

	CList<sDeviceBitmap*, sDeviceBitmap*>	mImagesCollection;

	CString			csAppFolder;

	CDeviceFont*	pDefaultDeviceFont;

	GLuint			oglPixelFormat;
	HGLRC			hRC;

public:
	// Scrolling data fields
	int				iXScrollOffset;
	int				iYScrollOffset;

	int				iMaxXScrollPos;
	int				iMaxYScrollPos;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};