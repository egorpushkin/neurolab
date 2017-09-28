#pragma once

#include "FactoryDefinitions.h"

class CDataFlowTest
{
public:
	verifier_routine_impl(PerformTest)
	{	
		if (ErrorsCount > 0)
		{
			// Skipping data flow test. Network contain errors
			ErrorsCount++;

			add_log_message("E0010", "Data flow test skipped. Network contains structure errors.", "Data Flow Test");
            return;
		}

		// Prepering data for data flow test
		CList<IElement*, IElement*>	mProcessors;

		enumerate_elements()
			if (pElement->GetElementType() == ET_PROCESSOR)
				mProcessors.AddTail(pElement);

		int** ppMatrix = new int*[mProcessors.GetCount()];
		for (int i = 0;i < mProcessors.GetCount();i++)
			ppMatrix[i] = new int[mProcessors.GetCount()];

		for (int i = 0;i < mProcessors.GetCount();i++)
			for (int j = 0;j < mProcessors.GetCount();j++)
			{
				if (i == j)
				{
					ppMatrix[i][j] = 0;

					continue;
				}

				ppMatrix[i][j] = GetElementsConnectionState(
					mProcessors.GetAt(mProcessors.FindIndex(i)),
					mProcessors.GetAt(mProcessors.FindIndex(j)));
			}

		bCircleFound = false;

		// Building routes
		for (int i = 0;i < mProcessors.GetCount();i++)
            PrepareRoutes(
				ppMatrix, 
				&mProcessors, 
				i, 
				ErrorsCount, 
				WarningsCount, 
				pLogProvider);

		// Removing temporary data
		for (int i = 0;i < mProcessors.GetCount();i++)
			delete[] ppMatrix[i];
		delete[] ppMatrix; 
	}

private:
	static int GetElementsConnectionState(IElement* pElement1, IElement* pElement2)
	{
		if (FindElementInConnectionsFactory(
			pElement1,
			DC_OUTPUTS_FACTORY,
			pElement2))
			return 1;

		if (FindElementInConnectionsFactory(
			pElement2,
			DC_OUTPUTS_FACTORY,
			pElement1))
			return -1;
	
		return 0;
	}

	static bool FindElementInConnectionsFactory(
		IElement*		pElement,
		int				iFactoryType,
		IElement*		pElementToBeFound)
	{
		IDataConnector* pDataConnector = NULL;
		pElement->QueryInterface(IDD_IDataConnector, (void**)&pDataConnector);
		if (!pDataConnector)
			return false;

		IConnectionsFactory* pConnectionFactory = 
			pDataConnector->GetConnectionsFactory(iFactoryType);
		if (!pConnectionFactory)
			return false;

		pConnectionFactory->CreateEnumerator(3);
		while (CConnection* pConnection = pConnectionFactory->GetNextConnection(3))
			if (pConnection->pElement == pElementToBeFound)
				return true;
	
		return false;
	}

	static void PrepareRoutes(
		// Algorithm data
		int**			ppMatrix,
		CList<IElement*, IElement*>* pProcessors,
		int				iElementIndex,
		// Env. data
		int&			ErrorsCount,
		int&			WarningsCount,
		ILogProvider*	pLogProvider)
	{
		int* pRoute = new int[pProcessors->GetCount()];
		pRoute[0] = iElementIndex;

		RecursiveRoutesManager(
			pRoute, 
			1,
			ppMatrix,
			pProcessors,
			iElementIndex,
			ErrorsCount,
			WarningsCount,
			pLogProvider);
	
		delete pRoute;
	}

	static void RecursiveRoutesManager(
		// Routes data
		int*			pRoute,
		int				iRouteIndex,
		// Algorithm data
		int**			ppMatrix,
		CList<IElement*, IElement*>* pProcessors,
		int				iElementIndex,
		// Env. data
		int&			ErrorsCount,
		int&			WarningsCount,
		ILogProvider*	pLogProvider)
	{
		for (int j = 0;j < pProcessors->GetCount();j++)
			if (ppMatrix[pRoute[iRouteIndex - 1]][j] == 1 &&
				!FindPointInRoute(pRoute, iRouteIndex, j))
			{
				if (j > iElementIndex)
				{
					pRoute[iRouteIndex] = j;

					RecursiveRoutesManager(
						pRoute,
						iRouteIndex + 1,
						ppMatrix,
						pProcessors,
						iElementIndex,
						ErrorsCount,
						WarningsCount,
						pLogProvider);
				} else 
					if (j == iElementIndex)
					{
						// Network circle has been found
						if (!bCircleFound)
						{
							ErrorsCount++;

							add_log_message("E0009", "Prepared network contains at least one circle.", "Data Flow Test");
							bCircleFound = true;
						}

						ErrorsCount++;
						
						// Displaying route information
						add_log_message("E0011", "Network circle found:", "Data Flow Test");	
						for (int i = 0;i < iRouteIndex;i++)
						{
							IElement* pElement = 
								pProcessors->GetAt(
									pProcessors->FindIndex(
										pRoute[i]		
									)
								);

							CString tmMessage =
								CString(_T("    Element ")) +
								PrepareElementName(pElement) +
								CString(_T("."));

							add_log_message("", tmMessage, "");	
						}
					}
			}	
	}

	static bool FindPointInRoute(
		int*			pRoute,
		int				iRouteLength,
		int				iPointIndex)
	{
		for (int i = 1;i < iRouteLength;i++)
			if (pRoute[i] == iPointIndex)
				return true;

		return false;
	}

	static CString PrepareElementName(IElement* pElement)
	{
		CString tmElementName;
		tmElementName.Format(
			"'%s %d'", 
			pElement->GetElementTitle(), 
			pElement->GetElementID());

        return tmElementName;
	}

public:
	static bool bCircleFound;
};

bool CDataFlowTest::bCircleFound = false;