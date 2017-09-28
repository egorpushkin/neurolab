#include "StdAfx.h"
#include ".\rbflayer.h"

#include "Math.h"

CRBFLayer::CRBFLayer(void)
{
	iMenuResourceID = IDR_ELEMENTS_POPUPS;
	iSubMenuResourceID = 8;

	csElementTitle = _T("RBF Layer");

	iElementType = ET_PROCESSOR;

	iImageWidth = 32;
	iImageHeight = 64;

	CreateWeights(64, 64);
}

CRBFLayer::~CRBFLayer(void)
{
	RemoveWeights();
}

// IElement implementations section
void CRBFLayer::CommandNotify(WPARAM wParam, LPARAM lParam)
{
	int iCmd = LOWORD(wParam);
	switch (iCmd)
	{
	case ID_RBFL_PROPERTIES:
		ShowLayerPropertiesDlg();
		break;	
	}

	CCmnElement::CommandNotify(wParam, lParam);
}

// IBuilderElement implementations section
void CRBFLayer::ShowElement()
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
	CString csBitmapName = CString("RBF_Layer_Passive");
	if (bIsSelected)
		csBitmapName = CString("RBF_Layer_Active");
	
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
		tmPoint.x - 29, tmPoint.y + 5, pDriver);

	// Drawing layer ID
	tmText.Format("RBFL %d", iElementID);

	pFont->RenderString(tmText, 
		tmPoint.x - 17, tmPoint.y - iImageHeight - 10, pDriver);
}

bool CRBFLayer::IsClicked(CPoint& point)
{
	CRect rRect(pntPosition.x - iImageWidth/2, 
		pntPosition.y,
		pntPosition.x + iImageWidth/2, 
		pntPosition.y + iImageHeight);

	return rRect.PtInRect(point);
}

CPoint CRBFLayer::GetPositionForConnectedElement(CConnection* pConnection)
{
	return CPoint(pntPosition.x, pntPosition.y + iImageHeight/2);
}

// IDataFlow implementations section
void CRBFLayer::ProcessElement()
{
	SplitConnectionsData(&mInputData, DC_INPUTS_FACTORY);

	if (mInputData.GetDataLength() != iInputsCount)
		return;
	if (mElementData.GetDataLength() != iLayerDimension)
		return;

	for (int i = 0;i < iLayerDimension;i++)
	{
		float fCenter = 0;
		
		for (int j = 0;j < iInputsCount;j++)
			fCenter += (pLayerWeights[j].GetItemData(i) - mInputData.GetItemData(j))*
				(pLayerWeights[j].GetItemData(i) - mInputData.GetItemData(j));
	
		fCenter *= -1;

		float fDelta = mDeltas.GetItemData(i);
	
		float fOut = fCenter;
		if (fDelta != 0)
			fOut /= (fDelta*fDelta);
		if (pActivateFunction)
			fOut = (pActivateFunction->pfnProcessFunction)(pActivateFunction, fOut);

		mElementData.SetItemData(i, fOut);
	}
}

void CRBFLayer::FlowData()
{
	FlowLayerData();
}

// IDataConnector implementations section

// ILayerCOntrol implementations section
bool CRBFLayer::ModifyWeights()
{
    return true;
}

// IStorageController implementations section
bool CRBFLayer::Serialize(CArchive& ar)
{
	CCmnElement::Serialize(ar);
	CCmnBuilderElement::Serialize(ar);
	CCmnDataFlow::Serialize(ar);
	CCmnDataConnector::Serialize(ar);
	CCmnLayerControl::Serialize(ar);

	mDeltas.Serialize(ar);

	if (ar.IsLoading())
	{} else	{}

	return true;
}

// IObject implementations section
CString CRBFLayer::GetClassString()
{
	return _T("CRBFLayer");
}

void CRBFLayer::QueryInterface(int iIDD, void** ppvObject)
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