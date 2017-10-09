#pragma once


// CBkGrSliderCtrl

class CBkGrSliderCtrl : public CSliderCtrl
{
	DECLARE_DYNAMIC(CBkGrSliderCtrl)

public:
	CBkGrSliderCtrl();
	virtual ~CBkGrSliderCtrl();

private:
	CDC			m_dcBk;
	CBitmap		m_bmpBk;
	CBitmap     *m_bmpBkOld;
	//CBitmap*	m_pbmpOldBk;
	CPen m_penThumb;
	CPen m_penThumbLight;
	CPen m_penThumbLighter;
	CPen m_penThumbDark;
	CPen m_penThumbDarker;
	COLORREF m_crThumb;
	COLORREF m_crThumbLight;
	COLORREF m_crThumbLighter;
	COLORREF m_crThumbDark;
	COLORREF m_crThumbDarker;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};


