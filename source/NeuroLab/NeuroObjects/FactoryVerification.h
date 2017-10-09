#pragma once

#include "FactoryDefinitions.h"

#include "DataFlowTest.h"

class CFactoryVerification
{
public:
	verifier_routine_impl(VerifyFactory)
	{	
		ASSERT(pElementsCollection != NULL);

		ErrorsCount = 0;
		WarningsCount = 0;

		clear_log();

		// Start log messages 
		add_log_message("", "--------------------------- Verification started ---------------------------", "");
		add_log_message("", "", "");

		// Preforming verifications
		verifier_routine(CheckElementsPresence);
		verifier_routine(CheckNetworkContent);
		verifier_routine(CheckForSingleElements);
		verifier_routine(CheckForWrongProcessors);
		verifier_routine(CheckLayerElements);		
		verifier_routine(CDataFlowTest::PerformTest);

		// Verification done
		CString tmMessage;
		tmMessage.Format(
			"    Network project - %d error(s), %d warning(s)", 
			ErrorsCount, 
			WarningsCount);

		if (ErrorsCount > 0 || WarningsCount > 0)
			add_log_message("", "", "");
		add_log_message("", tmMessage, "");
		add_log_message("", "----------------------------------- Done -----------------------------------", "");
	}

private:
	verifier_routine_impl(CheckElementsPresence)
	{
		pElementsCollection->CreateElementsEnumerator();
		if (!pElementsCollection->GetNextElement())
		{
			// Network is empty
			WarningsCount++;

			add_log_message("W0001", "Network does not contain any elements.", "Elements Presence");
		}	
	}

	verifier_routine_impl(CheckNetworkContent)
	{
		bool bHasInputs = false;
		bool bHasOutputs = false;

		enumerate_elements()
		{	
			if (pElement->GetElementType() == ET_INPUT)
				bHasInputs = true;

			if (pElement->GetElementType() == ET_OUTPUT)
				bHasOutputs = true;
		}

		if (!bHasInputs)
		{
			// Network does not contain any input elements.
			ErrorsCount++;

			add_log_message("E0012", "Network does not contain any input elements.", "Network Content");
		}

		if (!bHasOutputs)
		{
			// Network does not contain any output elements.
			ErrorsCount++;

			add_log_message("E0013", "Network does not contain any output elements.", "Network Content");
		}	
	}

	verifier_routine_impl(CheckForSingleElements)
	{
		enumerate_elements()
		{
			IDataConnector* pDataConnector = NULL;
			pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
			if (!pDataConnector)
				continue;

			int iHasConnections = 0;

			IConnectionsFactory* pConnectinoFactory = 
				pDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);
			if (pConnectinoFactory->GetConnectionsCount())
				iHasConnections++;

			pConnectinoFactory = 
				pDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);
			if (pConnectinoFactory->GetConnectionsCount())
				iHasConnections++;

			if (!iHasConnections)
			{
				// Element does not have any connections (input or output)
				ErrorsCount++;
				
				CString tmMessage = 
					CString(_T("Element ")) + 
					PrepareElementName(pElement) + 
					CString(_T(" has no any connections."));

				add_log_message("E0001", tmMessage, "Single Element");
			}			
		}	
	}

	verifier_routine_impl(CheckForWrongProcessors)
	{
		enumerate_elements()
		{
			if (pElement->GetElementType() == ET_PROCESSOR)
			{
				IDataConnector* pDataConnector = NULL;
				pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
				if (!pDataConnector)
					continue;

				IConnectionsFactory* pConnectinoFactory = 
					pDataConnector->GetConnectionsFactory(DC_INPUTS_FACTORY);
				if (!pConnectinoFactory->GetConnectionsCount())
				{
					// ET_PROCESSOR element does not have input connections
					ErrorsCount++;
					
					CString tmMessage = 
						CString(_T("ET_PROCESSOR element ")) + 
						PrepareElementName(pElement) + 
						CString(_T(" has no any input connections."));

					add_log_message("E0002", tmMessage, "Processors Check");					
				}

				pConnectinoFactory = 
					pDataConnector->GetConnectionsFactory(DC_OUTPUTS_FACTORY);
				if (!pConnectinoFactory->GetConnectionsCount())
				{
					// ET_PROCESSOR element does not have output connections
					ErrorsCount++;
					
					CString tmMessage = 
						CString(_T("ET_PROCESSOR element ")) + 
						PrepareElementName(pElement) + 
						CString(_T(" has no any output connections."));

					add_log_message("E0003", tmMessage, "Processors Check");					
				}
			}
		}
	}

	verifier_routine_impl(CheckLayerElements)
	{
		CDataFactory tmDataFactory;
		IDataFactory* pDataFactory = NULL;
		tmDataFactory.QueryInterface(IDD_IDataFactory, (void**)&pDataFactory);
		if (!pDataFactory)
			return;

		enumerate_elements()
		{
			ILayerControl* pLayerControl = NULL;
			pElement->QueryInterface(IDD_ILayerControl, (void**)&pLayerControl);
			if (!pLayerControl)
				continue;

			IDataFlow* pDataFlow = NULL;
			pElement->QueryInterface(IDD_IDataFlow, (void**)&pDataFlow);
			if (!pDataFlow)
				continue;

			if (pElement->GetElementType() == ET_INPUT)
			{
				pDataFlow->SplitConnectionsData(pDataFactory, DC_OUTPUTS_FACTORY);
				if (pDataFactory->GetDataLength() != pLayerControl->GetDimension())
				{
					// Input element is connected incorrectly
					ErrorsCount++;
					
					CString tmMessage = 
						CString(_T("ET_INPUT element ")) + 
						PrepareElementName(pElement) + 
						CString(_T(" is connected incorrectly."));

					add_log_message("E0004", tmMessage, "Layers Check");							
				}		
			}

			if (pElement->GetElementType() == ET_OUTPUT)
			{
				pDataFlow->SplitConnectionsData(pDataFactory, DC_INPUTS_FACTORY);
				if (pDataFactory->GetDataLength() != pLayerControl->GetDimension())
				{
					// Output element is connected incorrectly
					ErrorsCount++;
					
					CString tmMessage = 
						CString(_T("ET_OUTPUT element ")) + 
						PrepareElementName(pElement) + 
						CString(_T(" is connected incorrectly."));

					add_log_message("E0005", tmMessage, "Layers Check");							
				}		
			}

			if (pElement->GetElementType() == ET_PROCESSOR)
			{
				pDataFlow->SplitConnectionsData(pDataFactory, DC_INPUTS_FACTORY);
				if (pDataFactory->GetDataLength() != pLayerControl->GetInputsCount())
				{
					// Processor element has wrong input connections
					ErrorsCount++;
					
					CString tmMessage = 
						CString(_T("ET_PROCESSOR element ")) + 
						PrepareElementName(pElement) + 
						CString(_T(" has wrong input connections."));

					add_log_message("E0006", tmMessage, "Layers Check");							
				}		

				pDataFlow->SplitConnectionsData(pDataFactory, DC_OUTPUTS_FACTORY);
				if (pDataFactory->GetDataLength() != pLayerControl->GetDimension())
				{
					// Processor element has wrong output connections
					ErrorsCount++;
					
					CString tmMessage = 
						CString(_T("ET_PROCESSOR element ")) + 
						PrepareElementName(pElement) + 
						CString(_T(" has wrong output connections."));

					add_log_message("E0007", tmMessage, "Layers Check");							
				}		
			}

			if (pElement->GetSysName() == _T("HopfieldLayer") || 
				pElement->GetSysName() == _T("WinnerLayer"))
			{
				if (pLayerControl->GetInputsCount() != pLayerControl->GetDimension())
				{
					// Wrond Hopfield Layer element
					ErrorsCount++;
					
					CString tmMessage = 
						CString(_T("Element ")) + 
						PrepareElementName(pElement) + 
						CString(_T(" must have the same dimension and inputs count."));

					add_log_message("E0008", tmMessage, "Layers Check");
				}		
			}
		}
	}

	// Additional tools
	static CString PrepareElementName(IElement* pElement)
	{
		CString tmElementName;
		tmElementName.Format(
			"'%s %d'", 
			pElement->GetElementTitle(), 
			pElement->GetElementID());

        return tmElementName;
	}
};