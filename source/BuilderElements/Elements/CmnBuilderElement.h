#pragma once

#include "CmnElement.h"

class CCmnBuilderElement : public IBuilderElement
{
public:
	CCmnBuilderElement()
	{
		pBuilderControl = NULL;
		bIsSelected = false;

		iMenuResourceID = -1;
		iSubMenuResourceID = -1;
	}

	virtual bool Serialize(CArchive& ar)
	{
		if (ar.IsLoading())
		{
			ar.Read(&pntPosition.x, sizeof(int));
			ar.Read(&pntPosition.y, sizeof(int));
		} else
		{
			ar.Write(&pntPosition.x, sizeof(int));
			ar.Write(&pntPosition.y, sizeof(int));
		}

		return true;
	}

// IBuilderElement implementations section
	virtual void SetOutputControl(IBuilderControl* pControl)
	{
		pBuilderControl = pControl;
	}

	virtual IBuilderControl* GetOutputControl()
	{
		return pBuilderControl;
	}

	virtual void SetElementPosition(CPoint& Point)
	{
		pntPosition = Point;
	}

	virtual CPoint GetElementPosition()
	{
		return pntPosition;
	}

	virtual void SelectElement(bool bSelect)
	{
		bIsSelected = bSelect;
	}

	virtual bool IsSelected()
	{
		return bIsSelected;
	}

	virtual CPoint GetPositionForConnectedElement(CConnection* pConnection)
	{
		return GetElementPosition();
	}

	void TrackPopupMenu(CPoint& point)
	{
		if (iMenuResourceID == -1 || iSubMenuResourceID == -1)
			return;

		CMenu mMenu;
		BOOL bIsLoaded = mMenu.LoadMenu(iMenuResourceID);
		if (bIsLoaded)
		{
			CMenu* pSubMenu = mMenu.GetSubMenu(iSubMenuResourceID);
			if (pSubMenu)
			{
				CPoint tmMenuPos = point;
				pBuilderControl->GetControlWindow()->ClientToScreen(&tmMenuPos);

				pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,
					tmMenuPos.x, tmMenuPos.y, pBuilderControl->GetControlWindow());
			}		
		}
	}

// Data section
protected:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
	IBuilderControl*		pBuilderControl;

	CPoint					pntPosition;
	bool					bIsSelected;

	int						iMenuResourceID;
	int						iSubMenuResourceID;
};