#include "StdAfx.h"
#include ".\pcatransform.h"

#include "UITools/LayerPropertiesDlg.h"

CPCATranform::CPCATranform(void)
{
	iMenuResourceID = IDR_PCA_BLOCKSET;
	iSubMenuResourceID = 0;

	csElementTitle = _T("PCA Transform");

	iElementType = ET_PROCESSOR;

	iImageWidth = 32;
	iImageHeight = 64;

	CreateWeights(64, 64);
}

CPCATranform::~CPCATranform(void)
{
	RemoveWeights();
}

// IElement implementations section
void CPCATranform::CommandNotify(WPARAM wParam, LPARAM lParam)
{
	int iCmd = LOWORD(wParam);
	switch (iCmd)
	{
	case ID_PCA_PROPERTIES:
		ShowLayerPropertiesDlg();
		break;	           
	}

	CCmnElement::CommandNotify(wParam, lParam);
}

// IBuilderElement implementations section
void CPCATranform::ShowElement()
{
	IOutputDevice* pOutputDevice = NULL;
	pBuilderControl->QueryInterface(IDD_IOutputDevice, (void**)&pOutputDevice);
	IDeviceDriver* pDriver = pOutputDevice->GetDeviceDriver();

	IConnectionsFactory* pConnectionsFactory = GetConnectionsFactory(DC_INPUTS_FACTORY);

	CPoint tmPoint = pntPosition;
	tmPoint = pOutputDevice->TransformPoint(tmPoint);

	// Drawing inputs
	pDriver->Color3rgb(160, 160, 160);

	pConnectionsFactory->CreateEnumerator();
	while(CConnection* pConnection = pConnectionsFactory->GetNextConnection())
	{
		IBuilderElement* pDestBuilderElement = NULL;
		pConnection->pElement->QueryInterface(IDD_IBuilderElement, 
			(void**)&pDestBuilderElement);

		CPoint tmDestPoint = pDestBuilderElement->GetPositionForConnectedElement(pConnection->pOpposite);
		tmDestPoint = pOutputDevice->TransformPoint(tmDestPoint);
		
		CPoint tmSourcePoint = GetPositionForConnectedElement(pConnection);
		tmSourcePoint = pOutputDevice->TransformPoint(tmSourcePoint);

		if (pConnection->mWeights.GetDataLength() == 1)
			pDriver->LineWidth(1.0f); 
		else
			pDriver->LineWidth(2.0f);      

		pDriver->Begin(GL_LINES);     
		pDriver->Vertex3f(tmSourcePoint.x, tmSourcePoint.y, 0); 
		pDriver->Vertex3f(tmDestPoint.x, tmDestPoint.y, 0);  
		pDriver->End();
	}

	// Drawing layer
	CString csBitmapName = CString("PCA_Transform_Passive");
	if (bIsSelected)
		csBitmapName = CString("PCA_Transform_Active");
	
	sDeviceBitmap* pBitmap = pOutputDevice->GetImageByName(csBitmapName);

	float fTexX = iImageWidth*1.0f / pBitmap->pImage->sizeX;
	float fTexY = iImageHeight*1.0f / pBitmap->pImage->sizeY;

	pDriver->DrawTexturedQuad(pBitmap->iTextureID, 
		tmPoint.x - iImageWidth/2, tmPoint.y - iImageHeight, 
		tmPoint.x + iImageWidth/2, tmPoint.y, 
		1.0f, 
		0.0f, 0.0f, fTexX, fTexY);

	// Drawing layer title
	IDeviceFont* pFont = pOutputDevice->GetDefaultFont();

	CString	tmText = csElementTitle;
	tmText.MakeUpper();

	pFont->RenderString(tmText, 
		tmPoint.x - 45, tmPoint.y + 5, pDriver);

	// Drawing layer ID
	tmText.Format("PCAT %d", iElementID);

	pFont->RenderString(tmText, 
		tmPoint.x - 15, tmPoint.y - iImageHeight - 10, pDriver);
}

bool CPCATranform::IsClicked(CPoint& point)
{
	CRect rRect(pntPosition.x - iImageWidth/2, 
		pntPosition.y,
		pntPosition.x + iImageWidth/2, 
		pntPosition.y + iImageHeight);

	return rRect.PtInRect(point);
}

CPoint CPCATranform::GetPositionForConnectedElement(CConnection* pConnection)
{
	return CPoint(pntPosition.x, pntPosition.y + iImageHeight/2);
}

// IDataFlow implementations section
void CPCATranform::ProcessElement()
{
	SplitConnectionsData(&mInputData, DC_INPUTS_FACTORY);

	ProcessLayer();

	if (mOutputData.GetDataLength() == iLayerDimension)
		mElementData.SetData(mOutputData.GetData(), mOutputData.GetDataLength());
}

void CPCATranform::FlowData()
{
	FlowLayerData();
}

// IDataConnector implementations section

// ILayerCOntrol implementations section
bool CPCATranform::ModifyWeights()
{
    return true;
}

// IPCATransform implementations section

// IStorageController implementations section
bool CPCATranform::Serialize(CArchive& ar)
{
	CCmnElement::Serialize(ar);
	CCmnBuilderElement::Serialize(ar);
	CCmnDataFlow::Serialize(ar);
	CCmnDataConnector::Serialize(ar);
	CCmnLayer::Serialize(ar);

	if (ar.IsLoading())
	{} else	{}

	return true;
}

// IObject implementations section
CString CPCATranform::GetClassString()
{
	return _T("CPCATranform");
}

void CPCATranform::QueryInterface(int iIDD, void** ppvObject)
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
	case IDD_ILayerControl:
		*ppvObject = (ILayerControl*)this;
		break;
	case IDD_IStorageController:
		*ppvObject = (IStorageController*)this;
		break;
	}
}
// Private UI tools
void CPCATranform::ShowLayerPropertiesDlg()
{
	IElement* pElement = NULL;
	QueryInterface(IDD_IElement, (void**)&pElement);

	CLayerPropertiesDlg	mDlg;
	mDlg.SetElement(pElement);
	int iRes = mDlg.DoModal();
	if (iRes == IDOK)
	{
		if (GetDimension() != mDlg.mLayerDimension || 
			GetInputsCount() != mDlg.mInputsCount)
			CreateWeights(mDlg.mInputsCount, mDlg.mLayerDimension);
	}
}