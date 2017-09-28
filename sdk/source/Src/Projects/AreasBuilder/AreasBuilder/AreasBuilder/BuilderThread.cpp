#include "stdafx.h"
#include "BuilderThread.h"

#include "ErrorCodes.h"

#include "../UI/ProjectManager/ProjectManager.h"
#include "../UI/Interfaces/IStatusUIProvider.h"
#include "../UI/Common/Providers.h"

using namespace Workspace;
using namespace ProjectUI;
using namespace NetworkImportingKit;

namespace AreasBuilder
{

dword BuilderThread(void* pParam)
{
	ProjectManager* pProjectManager = (ProjectManager*)pParam;
	IStatusUIProvider* piStatusProvider = pProjectManager->GetStatusProvider();
	IAreasProject* piAreasProject = pProjectManager->GetAreasProject();

	// Step Initial. Receiving required contols
	INetworkProcessor* piNetProc = piAreasProject->GetNetworkProject()->GetProcessor();
	IElementsCollection* piNetElements = QueryTool<INetworkProcessor, IElementsCollection>::
		QueryInterface(piNetProc, IID_IElementsCollection);

	uint classesCount = piNetElements->GetOutputsCount();	
	uint inputVectorLength = piNetElements->GetInputsCount();

	uint wndWidth = piAreasProject->GetMapConfig()->GetUintParameter("wnd_width");
	uint wndHeight = piAreasProject->GetMapConfig()->GetUintParameter("wnd_height");
	uint wndLength = wndWidth * wndHeight;
	uint xStep = piAreasProject->GetMapConfig()->GetUintParameter("x_step");
	uint yStep = piAreasProject->GetMapConfig()->GetUintParameter("y_step");	

	uint imageWidth = piAreasProject->GetMultispecImage()->GetWidth();
	uint imageHeight = piAreasProject->GetMultispecImage()->GetHeight();

	uint mapWidth = (uint)floor(imageWidth * 1.0 / xStep);
	uint mapHeight = (uint)floor(imageHeight * 1.0 / yStep);
	uint mapLength = mapWidth * mapHeight;

	piAreasProject->GetAreasHolder()->SetMapDetails(mapWidth, mapHeight);

	// Messaging. Initialization
	//////////////////////////////////////////////////////////////////////////
	pProjectManager->ClearLog(PROCESSING_LOG);
	COleDateTime buildingStartedAt = COleDateTime::GetCurrentTime();	

	// Initial verification
	//////////////////////////////////////////////////////////////////////////
	uint wndFullLength = wndLength * piAreasProject->GetMultispecImage()->GetBandsCount();
	if (inputVectorLength != wndFullLength)
	{
		char msgInputs[MAX_PATH];
		char msgWindow[MAX_PATH];
		
		sprintf(msgInputs, "%d", inputVectorLength);
		sprintf(msgWindow, "%d", wndFullLength);

		String messageErrorDescr = 
			String(_T("A number of network project's inputs (")) + 
			String(msgInputs) +
			String(_T(") does not correspond to window's dimension (")) + 
			String(msgWindow) +
			String(_T(")."));

		String messageError = 
			String(_T("Project can not be built."));

		pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageErrorDescr);		
		pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageError);		

		pProjectManager->SetLastError(AB_E_CORRESPONDENCE);

		// Step Final. Release controls
		piNetElements->Release();
		piNetProc->Release();
		
		piAreasProject->Release();
		piStatusProvider->CloseModalDialog();
		piStatusProvider->Release();

		return 0;
	}

	// Step 1. Creating areas
	for (uint i = 0;i < classesCount;i++)
	{
		IDataFactory* piFactory = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
		piFactory->CreateFactory(mapLength, 0.3f);
		piAreasProject->GetAreasHolder()->AddArea(piFactory);
		piFactory->Release();
	}

	piStatusProvider->InitialUpdateUI();

	// Step 2. Preparing temporary objects
	IDataFactory* piInput = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
	piInput->CreateFactory(inputVectorLength);

	IDataFactory* piOutput = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
	piOutput->CreateFactory(classesCount);
	
	IDataFactory* piBandBlock = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
	piOutput->CreateFactory(wndLength);

	// Step 3. Building areas
	uint mapIndex = 0;
		
	for (uint j = 0;j < mapHeight;++j)	
	{
		for (uint i = 0;i < mapWidth;++i)
		{
			IBandsEnumerator* piBandsEnum = piAreasProject->GetMultispecImage()->GetBandsEnumerator();
			uint k = 0;
			for (bool hasBands = piBandsEnum->SelectFirst();hasBands;hasBands = piBandsEnum->SelectNext())
			{	
				// Prepare band fragment
				Band* pBand = piBandsEnum->GetSelected();

				IPGMBitmap* piPGMBand = pBand->GetBitmap();
				IDataBitmap* piRawBand = QueryTool<IPGMBitmap, IDataBitmap>::QueryInterface(piPGMBand, IID_IDataBitmap);

				piRawBand->GetDataFactory(i * xStep, j * yStep, wndWidth, wndHeight, piBandBlock);

				piRawBand->Release();
				piPGMBand->Release();

				// Prepare input data 
				memcpy(
					piInput->GetData() + k * wndLength, 
					piBandBlock->GetData(),
					wndLength * sizeof(float));

				++k;
			}
			piBandsEnum->Release();

			piNetProc->SetInputData(piInput);
			piNetProc->ProcessNetwork();
			piNetProc->GetOutputData(piOutput);

			for (uint k = 0;k < classesCount;k++)
				piAreasProject->GetAreasHolder()->GetArea(k)->SetItemData(
					j * mapWidth + i, 
					piOutput->GetItemData(k));

			++mapIndex;
			piStatusProvider->UpdatePercentage(mapIndex * 100 / mapLength);

			// Messaging
			//////////////////////////////////////////////////////////////////////////
			char position[MAX_PATH];
            sprintf(position, _T("%d x %d"), i * xStep, j * yStep);

			String message = 
				String(_T("Processing bitmap at position: ")) + 
				String(position);
			pProjectManager->DisplayLogMessage(PROCESSING_LOG, message);
			
			Sleep(0);

			if (pProjectManager->IsTerminationFlagSet())
			{
				String messageError = 
					String(_T("Project building terminated by user."));
				pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageError);		

				pProjectManager->SetLastError(AB_E_TERMINATED);

				// Step 4. Release temporary objects
				piInput->Release();
				piOutput->Release();
				piBandBlock->Release();

				// Step Final. Release controls
				piNetElements->Release();
				piNetProc->Release();
				
				piStatusProvider->CloseModalDialog();
				piStatusProvider->Release();

				piAreasProject->GetAreasHolder()->ReleaseAreas();
				piAreasProject->Release();

				return 0;
			}
		}
	}

	// Messaging. Complete statistics
	//////////////////////////////////////////////////////////////////////////
	COleDateTime buildingFinishedAt = COleDateTime::GetCurrentTime();	
	COleDateTimeSpan buildingPeriod = buildingFinishedAt - buildingStartedAt;	
	
	String messageBreak(_T(""));	
	String messageSplitLine(_T("--------------------------------------------------------------------------"));
	messageSplitLine = messageSplitLine + messageSplitLine + messageSplitLine;

	char msg[MAX_PATH];

	String messageReport(_T("    Complete report:"));
	String messageStarted = 
		String(_T("Building stared at: ")) + 
		String(buildingStartedAt.Format(_T("%H:%M:%S"))) + 
		String(_T("."));
	String messageFinished = 
		String(_T("Building finished at: ")) + 
		String(buildingFinishedAt.Format(_T("%H:%M:%S"))) + 
		String(_T("."));

	sprintf(msg, "%.1f", buildingPeriod.GetTotalSeconds());
	String messagePeriod = 
		String(_T("It took ")) + 
		String(msg) + 
		String(_T(" seconds to build the project."));

	sprintf(msg, "%.5f", buildingPeriod.GetTotalSeconds() / mapLength);
	String messageSinglePeriod = 
		String(_T("Average time required to process single image fragment with the use of neural netwotk is ")) + 
		String(msg) + 
		String(_T(" seconds."));

	sprintf(msg, "%d", mapLength);
	String messageTotalFragments = 
		String(msg) + 
		String(_T(" fragments were totally processed."));

	pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageBreak);
	pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageReport);
	pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageSplitLine);
	pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageStarted);
	pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageFinished);
	pProjectManager->DisplayLogMessage(PROCESSING_LOG, messagePeriod);
	pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageSinglePeriod);
	pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageTotalFragments);
	pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageSplitLine);
	pProjectManager->DisplayLogMessage(PROCESSING_LOG, messageBreak);

	// Finalize areas building
	piAreasProject->SetBuilt();

	// Step 4. Release temporary objects
	piInput->Release();
    piOutput->Release();
	piBandBlock->Release();
	
	// Step Final. Release controls
	piNetElements->Release();
    piNetProc->Release();

	piAreasProject->Release();
	piStatusProvider->AllowCloseDialog();
	piStatusProvider->Release();

	return 0;
}

}
