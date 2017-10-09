#include "StdAfx.h"
#include ".\hopfieldlayer.h"

CHopfieldLayer::CHopfieldLayer(void)
{
	iMenuResourceID = IDR_ELEMENTS_POPUPS;
	iSubMenuResourceID = 3;

	csElementTitle = _T("Hopfield Layer");

	iElementType = ET_PROCESSOR;

	iImageWidth = 32;
	iImageHeight = 64;

	CreateWeights(64, 64);
}

CHopfieldLayer::~CHopfieldLayer(void)
{
	RemoveWeights();
}

// Common functions
bool CHopfieldLayer::FindInFactoryPosition(CConnection* pConnection, int FactoryType, CPoint& pntPos)
{
	IConnectionsFactory* pFactory = GetConnectionsFactory(FactoryType);	
	
	int iConnectionsCount = pFactory->GetConnectionsCount();

	int iConnectionIndex = 0;
	
	float fSpace = 50;
	float fStep;
	if (iConnectionsCount == 1)
	{
		fStep = (iImageHeight - fSpace*2)*1.0f/2;
		iConnectionIndex = 1;
	}
	else
		fStep = (iImageHeight - fSpace*2)*1.0f/(iConnectionsCount - 1);

	pFactory->CreateEnumerator(1);
	while (CConnection* tmConnection = pFactory->GetNextConnection(1))
	{
		if (tmConnection == pConnection)
		{
			pntPos = CPoint(GetElementPosition().x, 
				GetElementPosition().y + fSpace + iConnectionIndex*fStep);

			return true;
		}
		iConnectionIndex++;
	}

	return false;
}

// IElement implementations section
void CHopfieldLayer::CommandNotify(WPARAM wParam, LPARAM lParam)
{
	int iCmd = LOWORD(wParam);
	switch (iCmd)
	{
	case ID_HL_PROPERTIES:
		ShowLayerPropertiesDlg();
		break;	
	}

	CCmnElement::CommandNotify(wParam, lParam);
}

// IBuilderElement implementations section
void CHopfieldLayer::ShowElement()
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
	CString csBitmapName = CString("Layer_Passive");
	if (bIsSelected)
		csBitmapName = CString("Layer_Active");
	
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
	tmText.Format("HL %d", iElementID);

	pFont->RenderString(tmText, 
		tmPoint.x - 10, tmPoint.y - iImageHeight - 10, pDriver);
}

bool CHopfieldLayer::IsClicked(CPoint& point)
{
	CRect rRect(pntPosition.x - iImageWidth/2, 
		pntPosition.y,
		pntPosition.x + iImageWidth/2, 
		pntPosition.y + iImageHeight);

	return rRect.PtInRect(point);
}

CPoint CHopfieldLayer::GetPositionForConnectedElement(CConnection* pConnection)
{
	CPoint pntPos;

	if (FindInFactoryPosition(pConnection, DC_INPUTS_FACTORY, pntPos))
		return pntPos;

	if (FindInFactoryPosition(pConnection, DC_OUTPUTS_FACTORY, pntPos))
		return pntPos;

	return CPoint(GetElementPosition().x, GetElementPosition().y + iImageHeight/2);
}

// IDataFlow implementations section
void CHopfieldLayer::ProcessElement()
{
	SplitConnectionsData(&mInputData, DC_INPUTS_FACTORY);

	if (!pLayerWeights || (iInputsCount != iLayerDimension) || 
		(iInputsCount != mInputData.GetDataLength()))
		return;

	bool bIsEquals = false;
	while (!bIsEquals)
	{
		ProcessLayer();

		bIsEquals = true;
		for (int i = 0;i < iLayerDimension;i++)
			if (mInputData.GetItemData(i) != mOutputData.GetItemData(i))
			{
				bIsEquals = false;
				break;
			}

		if (!bIsEquals)
			mInputData.SetData(mOutputData.GetData(), mOutputData.GetDataLength());
	}

	mElementData.SetData(mOutputData.GetData(), mOutputData.GetDataLength());
}

void CHopfieldLayer::FlowData()
{
	FlowLayerData();
}

// IDataConnector implementations section

// ILayerCOntrol implementations section
bool CHopfieldLayer::ModifyWeights()
{
	if (!pLayerWeights || (iInputsCount != iLayerDimension) || 
		(iInputsCount != mInputData.GetDataLength()))
		return false;

	for (int i = 0;i < iLayerDimension;i++)
		for (int j = 0;j < iLayerDimension;j++)
		{
			if (i == j)
			{
				pLayerWeights[i].SetItemData(j, 0.0f);
				continue;
			}

			pLayerWeights[i].IncreaseValue(j, 
				mInputData.GetItemData(i)*mInputData.GetItemData(j));
		}

    return true;
}

// IStorageController implementations section
bool CHopfieldLayer::Serialize(CArchive& ar)
{
	CCmnElement::Serialize(ar);
	CCmnBuilderElement::Serialize(ar);
	CCmnDataFlow::Serialize(ar);
	CCmnDataConnector::Serialize(ar);
	CCmnLayerControl::Serialize(ar);

	if (ar.IsLoading())
	{} else	{}

	return true;
}

// IObject implementations section
CString CHopfieldLayer::GetClassString()
{
	return _T("CHopfieldLayer");
}

void CHopfieldLayer::QueryInterface(int iIDD, void** ppvObject)
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