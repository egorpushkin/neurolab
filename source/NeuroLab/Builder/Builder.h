#pragma once

#include "CmnApp.h"
#include "CmnFactory.h"

#include "..\NeuronQuickInfoDlg.h"

class CBuilder : 
	public COutputDevice, 
	public IBuilderControl
{
	DECLARE_DYNAMIC(CBuilder)

public:
	CBuilder();
	virtual ~CBuilder();

	// Creating and initialization functions
	BOOL			CreateBuilder(CRect& rect, CWnd * pParentWnd, UINT ctrlId);
	void			SetAppController(IAppController* pController);

	// Elements placement functions
	CPoint			AttachElementToGrid(CPoint& ptAbsPosition, bool bOffsetPoint = false);
	IElement*		GetElementUnderMouse(CPoint& point);
	
	void			SelectElement(IElement* pElement);
	void			SelectElements(CPoint& point1, CPoint& point2);

	void			MoveSelectedElements(int XOffset, int YOffset, bool bAttachToGrid);

	// Drawing functions
	void			ShowElements(CDeviceDriver* pDriver);
	void			ShowSelectedZone(CDeviceDriver* pDriver);

// IBuilderControl declarations section	
	virtual CWnd*			GetControlWindow();
	virtual void			SetBuilderState(int iState);

	virtual void			SetActiveElement(IElement* pElement);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);
	
private:
	// Grig data fields
	int				iGridRange;
	bool			bShowGrid;
	bool			bAttachToGrid;

	// Neuro Factory & Application controller
	IElementsCollection* pNeuroFactory;
	IAppController* pAppController;

	// Builder state variables
	int				iBuilderState;
	CPoint			pntPrevDragPos;
	IElement*		pActiveElement;

	CNeuronQuickInfoDlg	mNeuronInfoDlg;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void	OnPaint();
	afx_msg void	OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void	OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void	OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void	OnRButtonUp(UINT nFlags, CPoint point);

	void			OnShowBuilderProperties();
	void			OnSelectAllElements();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};


