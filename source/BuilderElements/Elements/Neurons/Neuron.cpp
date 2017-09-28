#include "StdAfx.h"
#include ".\neuron.h"

#define N_TOP_ENUM			2

CNeuron::CNeuron(void)
{
	iMenuResourceID = IDR_ELEMENTS_POPUPS;
	iSubMenuResourceID = 1;

	csElementTitle = _T("Neuron");

	iElementType = ET_PROCESSOR;

	mElementData.CreateFactory(1);
}

CNeuron::~CNeuron(void)
{
}

// IElement implementations section

// IBuilderElement implementations section
void CNeuron::ShowElement()
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
	CString csBitmapName = CString("Neuron_Passive");
	if (bIsSelected)
		csBitmapName = CString("Neuron_Active");
	
	sDeviceBitmap* pBitmap = pOutputDevice->GetImageByName(csBitmapName);

	pDriver->DrawDeviceBitmap(pBitmap, 
		tmPoint.x - pBitmap->pImage->sizeX/2, tmPoint.y - pBitmap->pImage->sizeY/2); 
	
	// Drawing neuron ID
	IDeviceFont* pFont = pOutputDevice->GetDefaultFont();

	CString	tmText;
	tmText.Format("N %d", iElementID);

	pFont->RenderString(tmText, tmPoint.x - 8, tmPoint.y - 21, pDriver);
}

bool CNeuron::IsClicked(CPoint& Point)
{
	if ((Point.x-pntPosition.x)*(Point.x-pntPosition.x) +
		(Point.y-pntPosition.y)*(Point.y-pntPosition.y) < 100) 
		return true;
	return false;
}

// IDataFlow implementations section
void CNeuron::ProcessElement()
{
	IDataConnector* pDataConnector = NULL;
	QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
	IConnectionsFactory* pConnectionsFactory = pDataConnector->GetConnectionsFactory(
		DC_INPUTS_FACTORY);

	float fPreparedOutput = 0;

	pConnectionsFactory->CreateEnumerator(N_TOP_ENUM);
	while (CConnection* pConnection = pConnectionsFactory->GetNextConnection(N_TOP_ENUM))
	{
		for (int i = 0;i < pConnection->mData.GetDataLength();i++)
			fPreparedOutput += pConnection->mData.GetItemData(i)*pConnection->mWeights.GetItemData(i);
	}

	if (pActivateFunction)
		fPreparedOutput = (*pActivateFunction->pfnProcessFunction)(
			pActivateFunction, fPreparedOutput);

	mElementData.SetItemData(0, fPreparedOutput);
}

// IDataConnector implementations section

// IStorageController implementations section
bool CNeuron::Serialize(CArchive& ar)
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
CString CNeuron::GetClassString()
{
	return _T("CNeuron");
}

void CNeuron::QueryInterface(int iIDD, void** ppvObject)
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