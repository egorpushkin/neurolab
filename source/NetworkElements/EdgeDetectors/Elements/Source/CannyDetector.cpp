#include "StdAfx.h"
#include ".\CannyDetector.h"

#include "CommonUI\DataImagePropertiesDlg.h"
#include "UI\CannyDetectorParametersDlg.h"

#include "EdgeDetectionAlgorithms\CannyAlgorithm.h"

CCannyDetector::CCannyDetector(void)
{
	iMenuResourceID = IDR_ELEMENTS_POPUPS;
	iSubMenuResourceID = 0;

	csElementTitle = _T("Canny Detector");

	iElementType = ET_PROCESSOR;

	iImageWidth = 32;
	iImageHeight = 64;

	CreateWeights(64*64, 64*64);
}

CCannyDetector::~CCannyDetector(void)
{
	RemoveWeights();
}

// IElement implementations section
void CCannyDetector::CommandNotify(WPARAM wParam, LPARAM lParam)
{
	int iCmd = LOWORD(wParam);
	switch (iCmd)
	{
	case ID_DATA_IMAGE_PROPERTIES:
		ShowDataImagePropertiesDlg();
		break;	           
	case ID_CANNY_DETECTOR_PARAMETERS:
		ShowCannyDetectorParametersDlg();
		break;
	}

	CCmnElement::CommandNotify(wParam, lParam);
}

// IBuilderElement implementations section
void CCannyDetector::ShowElement()
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
	CString csBitmapName = CString("Canny_Detector_Passive");
	if (bIsSelected)
		csBitmapName = CString("Canny_Detector_Active");
	
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
		tmPoint.x - 47, tmPoint.y + 5, pDriver);

	// Drawing layer ID
	tmText.Format("CD %d", iElementID);

	pFont->RenderString(tmText, 
		tmPoint.x - 10, tmPoint.y - iImageHeight - 10, pDriver);
}

bool CCannyDetector::IsClicked(CPoint& point)
{
	CRect rRect(pntPosition.x - iImageWidth/2, 
		pntPosition.y,
		pntPosition.x + iImageWidth/2, 
		pntPosition.y + iImageHeight);

	return rRect.PtInRect(point);
}

CPoint CCannyDetector::GetPositionForConnectedElement(CConnection* pConnection)
{
	return CPoint(pntPosition.x, pntPosition.y + iImageHeight/2);
}

// IDataFlow implementations section
void CCannyDetector::ProcessElement()
{
	SplitConnectionsData(&mInputData, DC_INPUTS_FACTORY);

	IDataFactory* pInputData = NULL;
	mInputData.QueryInterface(IDD_IDataFactory, (void**)&pInputData);
	IDataFactory* pOutputData = NULL;
	mOutputData.QueryInterface(IDD_IDataFactory, (void**)&pOutputData);
	pOutputData->CreateFactory(mInputData.GetDataLength());

	ICannyDetectorControl* pCannyDetectorControl = NULL;
    QueryInterface(IDD_ICannyDetectorControl, (void**)&pCannyDetectorControl);

	CCannyAlgorithm	mCannyTool;
	mCannyTool.FindEdges(
		pInputData,
		pOutputData,
		pCannyDetectorControl);

	mElementData.SetData(mOutputData.GetData(), mOutputData.GetDataLength());
}

void CCannyDetector::FlowData()
{
	FlowLayerData();
}

// ILayerCOntrol implementations section
void CCannyDetector::CreateWeights(int Inputs, int Dimension)
{
	IDataFlow* pDataFlow = NULL;
	QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);	
	pDataFlow->GetDataFactory()->CreateFactory(Dimension);

	iLayerDimension = Dimension;
	iInputsCount = Inputs;
}

// IStorageController implementations section
bool CCannyDetector::Serialize(CArchive& ar)
{
	CCmnElement::Serialize(ar);
	CCmnBuilderElement::Serialize(ar);
	CCmnDataFlow::Serialize(ar);
	CCmnDataConnector::Serialize(ar);
	CCmnLayer::Serialize(ar);
	CCmnCannyDetectorImpl::Serialize(ar);

	if (ar.IsLoading())
	{} else {}

	return true;
}

// IObject implementations section
CString CCannyDetector::GetClassString()
{
	return _T("CCannyDetector");
}

void CCannyDetector::QueryInterface(int iIDD, void** ppvObject)
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
	case IDD_ICannyDetectorControl:
		*ppvObject = (ICannyDetectorControl*)this;
		break;
	case IDD_IStorageController:
		*ppvObject = (IStorageController*)this;
		break;
	}
}

// Scripting element UI tools
void CCannyDetector::ShowDataImagePropertiesDlg()
{
	CDataImagePropertiesDlg	mDlg;
	mDlg.mWidth = GetDataImageWidth();
	mDlg.mHeight = GetDataImageHeight();
	
	int iRes = mDlg.DoModal();
	if (iRes == IDOK)
	{
		SetDataImageWidth(mDlg.mWidth);
		SetDataImageHeight(mDlg.mHeight);

		int iDimension = mDlg.mWidth * mDlg.mHeight;
		if (GetDimension() != iDimension)
			CreateWeights(iDimension, iDimension);
	}
}

void CCannyDetector::ShowCannyDetectorParametersDlg()
{
	CCannyDetectorParametersDlg mDlg;

	mDlg.mSigmaX = GetGaussianSigmaX();
	mDlg.mSigmaY = GetGaussianSigmaY();
	mDlg.mCannyFraction = GetCannyFraction();
	mDlg.mLowThreshold = GetCannyLowThreshold();
	mDlg.mHighThreshold = GetCannyHighThreshold();
	mDlg.mMinSegmentLength = GetMinLengthOfSegment();
	mDlg.mMaxDeviation = GetMaxDeviation();    	
	
	int iRes = mDlg.DoModal();
	if (iRes == IDOK)
	{
		SetGaussianSigmaX(mDlg.mSigmaX);
		SetGaussianSigmaY(mDlg.mSigmaY);
		SetCannyFraction(mDlg.mCannyFraction);
		SetCannyLowThreshold(mDlg.mLowThreshold);
		SetCannyHighThreshold(mDlg.mHighThreshold);
		SetMinLengthOfSegment(mDlg.mMinSegmentLength);
		SetMaxDeviation(mDlg.mMaxDeviation);    	
	}
}