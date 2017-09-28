#include "StdAfx.h"
#include ".\ScriptingElement.h"

#include "UI\ScriptingElementCodeDlg.h"
#include "UI\ScriptingElementWeightsDlg.h"
#include "CommonUI\LayerPropertiesDlg.h"

#include "LuaProcessor\LuaProcessor.h"

CScriptingElement::CScriptingElement(void)
{
	iMenuResourceID = IDR_ELEMENTS_POPUPS;
	iSubMenuResourceID = 0;

	csElementTitle = _T("Scripting Element");

	iElementType = ET_PROCESSOR;

	iImageWidth = 32;
	iImageHeight = 64;

	CreateWeights(64, 64);
	CreateWeightsSE(64, 64);
}

CScriptingElement::~CScriptingElement(void)
{
	RemoveWeights();
	RemoveWeightsSE();
}

// IElement implementations section
void CScriptingElement::CommandNotify(WPARAM wParam, LPARAM lParam)
{
	int iCmd = LOWORD(wParam);
	switch (iCmd)
	{
	case ID_LAYER_PROPERTIES:
		ShowLayerPropertiesDlg();
		break;	           
	case ID_SCRIPTS_ELEMENT_CODE:
        ShowProcessScriptEditor();
		break;
	case ID_SCRIPTS_ELEMENT_WEIGHTS:
		ShowWeightsMatrixDlg();
		break;
	}

	CCmnElement::CommandNotify(wParam, lParam);
}

// IBuilderElement implementations section
void CScriptingElement::ShowElement()
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
	CString csBitmapName = CString("Scripting_Element_Passive");
	if (bIsSelected)
		csBitmapName = CString("Scripting_Element_Active");
	
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
		tmPoint.x - 55, tmPoint.y + 5, pDriver);

	// Drawing layer ID
	tmText.Format("SE %d", iElementID);

	pFont->RenderString(tmText, 
		tmPoint.x - 10, tmPoint.y - iImageHeight - 10, pDriver);
}

bool CScriptingElement::IsClicked(CPoint& point)
{
	CRect rRect(pntPosition.x - iImageWidth/2, 
		pntPosition.y,
		pntPosition.x + iImageWidth/2, 
		pntPosition.y + iImageHeight);

	return rRect.PtInRect(point);
}

CPoint CScriptingElement::GetPositionForConnectedElement(CConnection* pConnection)
{
	return CPoint(pntPosition.x, pntPosition.y + iImageHeight/2);
}

// IDataFlow implementations section
void CScriptingElement::ProcessElement()
{
	SplitConnectionsData(&mInputData, DC_INPUTS_FACTORY);

	// Preparing data for the global storage
	IElement* pElement = NULL;
	QueryInterface(IDD_IElement, (void**)&pElement);

	IDataFactory* pInputData = NULL;
	mInputData.QueryInterface(IDD_IDataFactory, (void**)&pInputData);
	IDataFactory* pOutputData = NULL;
	mOutputData.QueryInterface(IDD_IDataFactory, (void**)&pOutputData);

	// Executing script
	CLuaProcessor tmProcessor;
	tmProcessor.ProcessElement(
		csProcessElementScript,
		pElement,
		pInputData,
		pOutputData);

	// Updating layer output signals
	if (mOutputData.GetDataLength() == iLayerDimension)
		mElementData.SetData(mOutputData.GetData(), mOutputData.GetDataLength());
}

void CScriptingElement::FlowData()
{
	FlowLayerData();
}

// IDataConnector implementations section

// ILayerCOntrol implementations section

// IScriptingElementControl declarations section
void CScriptingElement::CreateWeightsSE(int Inputs, int Dimension)
{
	if (pLayerWeights && iLayerDimensionSE > 0 && iInputsCountSE > 0)
		RemoveWeightsSE();

	pLayerWeights = new CDataFactory[Inputs];        	
	for (int i = 0;i < Inputs;i++)
		pLayerWeights[i].CreateFactory(Dimension);

	IDataFlow* pDataFlow = NULL;
	QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);
	
	pDataFlow->GetDataFactory()->CreateFactory(Dimension);

	mDeltas.CreateFactory(Dimension);

	iLayerDimensionSE = Dimension;
	iInputsCountSE = Inputs;
}

void CScriptingElement::RemoveWeightsSE()
{
	CCmnLayer::RemoveWeights();

	iLayerDimensionSE = 0;
	iInputsCountSE = 0;
}

// IStorageController implementations section
bool CScriptingElement::Serialize(CArchive& ar)
{
	CCmnElement::Serialize(ar);
	CCmnBuilderElement::Serialize(ar);
	CCmnDataFlow::Serialize(ar);
	CCmnDataConnector::Serialize(ar);
	CCmnScriptingElement::Serialize(ar);
	CCmnSELayer::Serialize(ar);

	if (ar.IsLoading())
	{} else {}

	return true;
}

// IObject implementations section
CString CScriptingElement::GetClassString()
{
	return _T("CScriptingElement");
}

void CScriptingElement::QueryInterface(int iIDD, void** ppvObject)
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
	case IDD_IScriptingElementControl:
		*ppvObject = (IScriptingElementControl*)this;
		break;
	case IDD_IStorageController:
		*ppvObject = (IStorageController*)this;
		break;
	}
}

// Scripting element UI tools
void CScriptingElement::ShowProcessScriptEditor()
{
	CScriptingElementCodeDlg mDlg;
	mDlg.mScriptCode = csProcessElementScript;
	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		csProcessElementScript = mDlg.mScriptCode;
	}
}

void CScriptingElement::ShowLayerPropertiesDlg()
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

void CScriptingElement::ShowWeightsMatrixDlg()
{
	IElement* pElement = NULL;
	QueryInterface(IDD_IElement, (void**)&pElement);

	CScriptingElementWeightsDlg mDlg;
	mDlg.SetElement(pElement);
	int res = mDlg.DoModal();
	if (res == IDOK)
	{
		if (GetDimension() != mDlg.mLayerDimension || 
			GetInputsCount() != mDlg.mInputsCount)
		{
			if (mDlg.mLayerDimension && mDlg.mInputsCount)
				CreateWeightsSE(mDlg.mInputsCount, mDlg.mLayerDimension);		
			else
				RemoveWeightsSE();
		}	
	}
}