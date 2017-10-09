#pragma once

#include "CmnElement.h"
#include "CmnFactory.h"

class CCmnElement : public IElement
{
public:
	CCmnElement()
	{
		iElementID = -1;
		csElementTitle = _T("");
	}

	// Custom operations
	void RemoveElement()
	{
		// Query needed interface IElementsCollection
		IBuilderElement* pBuilderElement = NULL;
		QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);
		
		IBuilderControl* pBuilderControl = pBuilderElement->GetOutputControl();

		IElementsCollection* pElementsCollection = NULL;
		pBuilderControl->QueryInterface(IDD_IElementsCollection, (void**)&pElementsCollection);

		// process element removing
		pBuilderControl->SetActiveElement(NULL);
		pElementsCollection->RemoveElement((IElement*)this);	
	}

	void SetAddConnectionState(int iState)
	{
		// Query required interfaces
		IBuilderElement* pBuilderElement = NULL;
		QueryInterface(IDD_IBuilderElement, (void**)&pBuilderElement);
		
		IBuilderControl* pBuilderControl = pBuilderElement->GetOutputControl();

		IDataConnector* pDataConnector = NULL;
		QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);

		// process connecting preparing
		pBuilderControl->SetBuilderState(BS_CONNECTING);
		pDataConnector->SetAddConnectionState(iState, 1);
	}

	virtual bool Serialize(CArchive& ar)
	{
		if (ar.IsLoading())
		{
			ar.Read(&iElementID, sizeof(int));
			ar.ReadString(csElementTitle);
		} else
		{
			ar.WriteString(csSysName); ar.Write("\n",1);
			ar.WriteString(csSysTitle); ar.Write("\n",1);

			ar.Write(&iElementID, sizeof(int));
			ar.WriteString(csElementTitle); ar.Write("\n",1);
		}

		return true;
	}

// IElement implementations section
	virtual void SetElementID(int iID)
	{
		iElementID = iID;
	}
	
	virtual int GetElementID()
	{
		return iElementID;
	}

	virtual CString GetElementTitle()
	{
		return csElementTitle;
	}

	virtual void SetSysName(CString& Name)
	{
		csSysName = Name;
	}

	virtual void			SetSysTitle(CString& Title)
	{
		csSysTitle = Title;
	}

	virtual CString GetSysName()
	{
		return csSysName;
	}

	virtual int GetElementType()
	{
		return iElementType;
	}

	virtual void CommandNotify(WPARAM wParam, LPARAM lParam)
	{
		int iCmd = LOWORD(wParam);
		switch (iCmd)
		{
		case ID_REMOVE:
			RemoveElement();
			break;	
		case ID_ADD_DENDRITE:			
			SetAddConnectionState(DC_INPUTS_FACTORY);			
			break;
		case ID_ADD_AXON:			
			SetAddConnectionState(DC_OUTPUTS_FACTORY);			
			break;
		}
	}	

protected:
	int						iElementID;
	CString					csElementTitle;

	CString					csSysName;
	CString					csSysTitle;

	int						iElementType;
};