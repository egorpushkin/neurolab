#pragma once


// CDataImageCtrlMarkerDlg dialog

class CDataImageCtrlMarkerDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataImageCtrlMarkerDlg)

public:
	CDataImageCtrlMarkerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDataImageCtrlMarkerDlg();

// Dialog Data
	enum { IDD = IDD_DATA_IMAGE_CTRL_MARKER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float mMarker;
	int mMarkerDiameter;
};
