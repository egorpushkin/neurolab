#include "StdAfx.h"
#include ".\output.h"

#define O_TOP_ENUM			2

COutput::COutput(void)
{
	iMenuResourceID = IDR_ELEMENTS_POPUPS;
	iSubMenuResourceID = 2;

	csElementTitle = _T("Output");

	iElementType = ET_OUTPUT;

	mElementData.CreateFactory(1);
}

COutput::~COutput(void)
{
}

// IElement implementations section

// IBuilderElement implementations section
void COutput::ShowElement()
{
	IOutputDevice* pOutputDevice = NULL;
	pBuilderControl->QueryInterface(IDD_IOutputDevice, (void**)&pOutputDevice);
	IDeviceDriver* pDriver = pOutputDevice->GetDeviceDriver();

	IConnectionsFactory* pConnectionsFactory = GetConnectionsFactory(DC_INPUTS_FACTORY);

	CPoint tmPoint = pntPosition;
	tmPoint = pOutputDevice->TransformPoint(tmPoint);

	// Drawing inputs
	pDriver->LineWidth(1.0f);      
	pDriver->Color3rgb(160, 160, 160);

	pConnectionsFactory->CreateEnumerator();
	while(CConnection* pConnection = pConnectionsFactory->GetNextConnection())
	{
		IBuilderElement* pDestBuilderElement = NULL;
		pConnection->pElement->QueryInterface(IDD_IBuilderElement, 
			(void**)&pDestBuilderElement);

		CPoint tmDestPoint = pDestBuilderElement->GetPositionForConnectedElement(pConnection->pOpposite);
		tmDestPoint = pOutputDevice->TransformPoint(tmDestPoint);

		if (pConnection->mWeights.GetDataLength() == 1)
			pDriver->LineWidth(1.0f); 
		else
			pDriver->LineWidth(2.0f); 

		pDriver->Begin(GL_LINES);     
		pDriver->Vertex3f(tmPoint.x, tmPoint.y, 0); 
		pDriver->Vertex3f(tmDestPoint.x, tmDestPoint.y, 0);  
		pDriver->End();
	}

	// Drawing neuron
	CString csBitmapName = CString("Output_Passive");
	if (bIsSelected)
		csBitmapName = CString("Output_Active");
	
	sDeviceBitmap* pBitmap = pOutputDevice->GetImageByName(csBitmapName);

	pDriver->DrawDeviceBitmap(pBitmap, 
		tmPoint.x - pBitmap->pImage->sizeX/2, tmPoint.y - pBitmap->pImage->sizeY/2); 
	
	// Drawing neuron ID
	IDeviceFont* pFont = pOutputDevice->GetDefaultFont();

	CString		tmText;
	tmText.Format("O %d", iElementID);

	pFont->RenderString(tmText, tmPoint.x - 3, tmPoint.y - 15, pDriver);
}

bool COutput::IsClicked(CPoint& point)
{
	if (((point.x-pntPosition.x)*(point.x-pntPosition.x) +
		(point.y-pntPosition.y)*(point.y-pntPosition.y) < 25) ||
		(abs(point.y-pntPosition.y) <= 5 && point.x >= pntPosition.x &&
		point.x <= pntPosition.x + 10))
		return true;
	return false;	 
}

// IDataFlow implementations section
void COutput::ProcessElement()
{
	IConnectionsFactory* pConnectionsFactory = GetConnectionsFactory(DC_INPUTS_FACTORY);

	CConnection* pConnection = NULL;

	pConnectionsFactory->CreateEnumerator(O_TOP_ENUM);
	while (pConnection = pConnectionsFactory->GetNextConnection(O_TOP_ENUM))
		break;

	if (pConnection)
		mElementData.SetItemData(0, pConnection->mData.GetItemData(0));
}

// IDataConnector implementations section

// IStorageController implementations section
bool COutput::Serialize(CArchive& ar)
{
	CCmnElement::Serialize(ar);
	CCmnBuilderElement::Serialize(ar);
	CCmnDataFlow::Serialize(ar);
	CCmnDataConnector::Serialize(ar);

	if (ar.IsLoading())
	{} else	{}

	return true;
}

// IObject implementations section
CString COutput::GetClassString()
{
	return _T("COutput");
}

void COutput::QueryInterface(int iIDD, void** ppvObject)
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