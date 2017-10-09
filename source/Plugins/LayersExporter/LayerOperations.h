#pragma once

#include "CmnApp.h"
#include "CmnFactory.h"

#include "LayerSerialize.h"

class CLayerOperations
{
public:
	static void FillLayersList(
		IAppController*		pAppController,
		CListCtrl*			pListCtrl)
	{
		IElementsCollection* pElementsCollection = NULL;
		pAppController->QueryInterface(
			IDD_IElementsCollection, 
			(void**)&pElementsCollection);

		ASSERT(pElementsCollection != NULL);

		pElementsCollection->CreateElementsEnumerator(USER_ENUMERATOR_RANGE_FROM);
		while (IElement* pElement = pElementsCollection->GetNextElement(USER_ENUMERATOR_RANGE_FROM))
		{
			ILayerControl* pLayerControl = NULL;
			pElement->QueryInterface(
				IDD_ILayerControl, 
				(void**)&pLayerControl);

			if (!pLayerControl)
				continue;

			CString tmName, tmID, tmType, tmDimmension, tmInputs;

			tmName = pElement->GetElementTitle();
			tmID.Format("%d", pElement->GetElementID());

			switch (pElement->GetElementType())
			{
			case ET_INPUT:
				tmType = _T("ET_INPUT");
				break;
			case ET_OUTPUT:
				tmType = _T("ET_OUTPUT");
				break;
			case ET_PROCESSOR:
				tmType = _T("ET_PROCESSOR");
				break;
			}

			tmDimmension.Format("%d", pLayerControl->GetDimension());
			tmInputs.Format("%d", pLayerControl->GetInputsCount());

			AddListItem(pListCtrl, -1, (LPARAM)pElement, 5,
				tmName, tmID, tmType, tmInputs, tmDimmension);
		}
	}

	static bool ExportLayerData(
		IElement* pElement)
	{
		ILayerControl* pLayerControl = NULL;
		pElement->QueryInterface(
			IDD_ILayerControl, 
			(void**)&pLayerControl);
		if (!pLayerControl)
			return false;

		CFileDialog	mFileDlg(FALSE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Layer Data File v1.0|*.nllayerd||");
		INT_PTR res = mFileDlg.DoModal();
		if (res == IDOK)
		{
			CFile mSaveFile;
			if (mSaveFile.Open(mFileDlg.GetPathName(), CFile::modeCreate|CFile::modeWrite, NULL))
			{
				CArchive mArchive(&mSaveFile, CArchive::store);

				CLayerSerializer mSerializer;
				mSerializer.StoreLayerData(pLayerControl, mArchive);
                
				mArchive.Close();
				mSaveFile.Close();

				AfxMessageBox("Layer data has been successfully exported.");

				return true;
			}		
		}
	
		return false;
	}

	static bool ImportLayerData(
		IElement* pElement)
	{
		ILayerControl* pLayerControl = NULL;
		pElement->QueryInterface(
			IDD_ILayerControl, 
			(void**)&pLayerControl);
		if (!pLayerControl)
			return false;

		CFileDialog	mFileDlg(TRUE, "", "", OFN_OVERWRITEPROMPT, "Neuro Laboratory Layer Data File v1.0|*.nllayerd||");
		INT_PTR res = mFileDlg.DoModal();
		if (res == IDOK)
		{
			CFile mLoadFile;
			if (mLoadFile.Open(mFileDlg.GetPathName(), CFile::modeRead, NULL))
			{
				CArchive mArchive(&mLoadFile, CArchive::load);

				CLayerSerializer mSerializer;
				if (!mSerializer.LoadLayerHeader(mArchive))
				{
                    AfxMessageBox("Wrong layer data file specified.");				
					
					mArchive.Close();
					mLoadFile.Close();					

					return false;
				}

				if (mSerializer.GetLayerInputsCount() != pLayerControl->GetInputsCount() ||
					mSerializer.GetLayerDimension() != pLayerControl->GetDimension())
				{
					CString tmMessage = 
						CString(_T("Selected layer and data source have different dimensions or number of inputs.\n"));
					CString tmDetails;
					tmDetails.Format("Data source inputs count: %d.\nData source dimension: %d.", 
						mSerializer.GetLayerInputsCount(),
						mSerializer.GetLayerDimension());

					tmMessage += tmDetails;

                    AfxMessageBox(tmMessage);

					mArchive.Close();
					mLoadFile.Close();					

					return false;
				}

				if (mSerializer.GetElementSysName() != pElement->GetSysName())
				{				
					CString tmMessage =
						CString(_T("Selected layer and data source are not of the same kind. ")) +
						CString(_T("Are you sure that you want to load data in any case?\n")) +
						CString(_T("Data source layer: ")) + mSerializer.GetElementTitle() + CString(_T(".\n")) + 
						CString(_T("Selected layer: ")) + pElement->GetElementTitle() + CString(_T("."));

					int iRes = AfxMessageBox(tmMessage, MB_YESNO);
					if (iRes != IDYES)
					{
						mArchive.Close();
						mLoadFile.Close();					

						return false;
					}
				}

				mSerializer.LoadLayerData(
					pLayerControl,
					mArchive);			
			
				mArchive.Close();
				mLoadFile.Close();

				AfxMessageBox("Layer data has been successfully imported.");

				return true;
			}		
		}

		return false;
	}

private:
	// UI Tools
	static void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...)
	{
		LV_ITEM item;
		item.iItem = m_List->GetItemCount();
		item.iImage = icon;
		item.lParam = data;
	   
		item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

		va_list params;
		va_start(params, num);
		char * temp = va_arg(params,char *);

		item.iSubItem = 0;
		item.pszText = temp;
		m_List->InsertItem(&item);

		for(int i = 1;i<num;i++)
		{
			temp = va_arg(params,char *);
			item.mask = LVIF_TEXT;
			item.iSubItem = i;
			item.pszText = temp;
			m_List->SetItem(&item);
		}
	} 
};