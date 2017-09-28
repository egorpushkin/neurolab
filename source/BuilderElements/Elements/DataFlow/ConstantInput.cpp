#include "StdAfx.h"
#include ".\constantinput.h"

#include "CIPropDlg.h"

CConstantInput::CConstantInput(void)
{
	iMenuResourceID = IDR_ELEMENTS_POPUPS;
	iSubMenuResourceID = 7;

	csElementTitle = _T("Constant Input");

	iElementType = ET_INPUT;

	mElementData.CreateFactory(1, 1.0f);
}

CConstantInput::~CConstantInput(void)
{
}

// Custom functions	
void CConstantInput::ShowPropertiesDlg()
{
	CCIPropDlg mDlg;
	mDlg.mValue = mElementData.GetItemData(0);
	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		mElementData.SetItemData(0, mDlg.mValue);
	}
}

// IElement implementations section
void CConstantInput::CommandNotify(WPARAM wParam, LPARAM lParam)
{
	int iCmd = LOWORD(wParam);
	switch (iCmd)
	{
	case ID_CI_PROPERTIES:
		ShowPropertiesDlg();
		break;	
	}

	CCmnElement::CommandNotify(wParam, lParam);
}

// IBuilderElement implementations section
void CConstantInput::ShowElement()
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

	pFont->RenderString(CString("Const"), tmPoint.x - 13, tmPoint.y + 8, pDriver);	

	CString tmText;
	tmText.Format("C %d", iElementID);

	pFont->RenderString(tmText, tmPoint.x - 8, tmPoint.y - 15, pDriver);	
}

bool CConstantInput::IsClicked(CPoint& Point)
{
	if ((Point.x-pntPosition.x)*(Point.x-pntPosition.x) +
		(Point.y-pntPosition.y)*(Point.y-pntPosition.y) < 25) 
		return true;
	return false;
}

// IDataFlow implementations section
bool CConstantInput::RequireData()
{
	return false;
}

// IDataConnector implementations section

// IStorageController implementations section
bool CConstantInput::Serialize(CArchive& ar)
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
CString CConstantInput::GetClassString()
{
	return _T("CConstantInput");
}

void CConstantInput::QueryInterface(int iIDD, void** ppvObject)
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
