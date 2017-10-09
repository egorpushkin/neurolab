#include "StdAfx.h"
#include ".\input.h"

CInput::CInput(void)
{
	iMenuResourceID = IDR_ELEMENTS_POPUPS;
	iSubMenuResourceID = 0;

	csElementTitle = _T("Input");

	iElementType = ET_INPUT;

	mElementData.CreateFactory(1);
}

CInput::~CInput(void)
{
}

// IElement implementations section

// IBuilderElement implementations section
void CInput::ShowElement()
{
	IOutputDevice* pOutputDevice = NULL;
	pBuilderControl->QueryInterface(IDD_IOutputDevice, (void**)&pOutputDevice);
	IDeviceDriver* pDriver = pOutputDevice->GetDeviceDriver();

	CPoint tmPoint = pntPosition;
	tmPoint = pOutputDevice->TransformPoint(tmPoint);

	// Drawing input device
	CString csBitmapName = CString("Input_Passive");
	if (bIsSelected)
		csBitmapName = CString("Input_Active");
	
	sDeviceBitmap* pBitmap = pOutputDevice->GetImageByName(csBitmapName);

	pDriver->DrawDeviceBitmap(pBitmap, 
		tmPoint.x - pBitmap->pImage->sizeX/2, tmPoint.y - pBitmap->pImage->sizeY/2); 

	// Drawing input ID
	IDeviceFont* pFont = pOutputDevice->GetDefaultFont();

	CString tmText;
	tmText.Format("X %d", iElementID);

	pFont->RenderString(tmText, tmPoint.x - 8, tmPoint.y - 15, pDriver);	
}

bool CInput::IsClicked(CPoint& Point)
{
	if ((Point.x-pntPosition.x)*(Point.x-pntPosition.x) +
		(Point.y-pntPosition.y)*(Point.y-pntPosition.y) < 25) 
		return true;
	return false;
}

// IDataFlow implementations section

// IDataConnector implementations section

// IStorageController implementations section
bool CInput::Serialize(CArchive& ar)
{
	CCmnElement::Serialize(ar);
	CCmnBuilderElement::Serialize(ar);
	CCmnDataFlow::Serialize(ar);
	CCmnDataConnector::Serialize(ar);

	if (ar.IsLoading())
	{	
	} else 
	{	
	}

	return true;
}

// IObject implementations section
CString CInput::GetClassString()
{
	return _T("CInput");
}

void CInput::QueryInterface(int iIDD, void** ppvObject)
{
	*ppvObject = NULL;
	switch (iIDD)
	{
	case IDD_IElement:
		*ppvObject = (IElement*)this;
		break;
	case IDD_IBuilderElement:
		*ppvObject = (IBuilderElement*)this;
		break;	
	case IDD_IDataFlow:
		*ppvObject = (IDataFlow*)this;
		break;
	case IDD_IDataConnector:
		*ppvObject = (IDataConnector*)this;
		break;
	case IDD_IStorageController:
		*ppvObject = (IStorageController*)this;
		break;
	}
}