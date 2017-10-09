#pragma once

#include "../CmnConverter.h"
#include "../CmnLog.h"

#include "Operation_LoadImage.h"

#define add_log_message(message) pLog->AddLogMessage(	CString(_T("")), \
														CString(_T(message)), \
														CString(_T("")))

class CCollectionConverterOperation_Convert
{
public:
	static bool ProcessConverting(
		CCollectionConverter*		pConverter, 
		CString&					FileName,
		int							SymbolDimension, 
		ILogProvider*				pLog)
	{
		if (pConverter->GetItemsCount() == 0)
		{
			add_log_message("There are no any converting items to build data file content.");
			return false;
		}

		add_log_message("Creating empty data file.");

		CDataFile mDataFile;
		mDataFile.CreateNewFile(
			SymbolDimension, 
			pConverter->GetDataFile()->GetOutputSymbolLength());

		add_log_message("Enumeration converting items...");
		
		pConverter->CreateEnumerator();
		while (CConverterItem* pItem = pConverter->GetNextItem())
		{
			CString tmProjectItemString;
			tmProjectItemString.Format(" Processing item: Group(%s) Symbol(%d)...", 
				pItem->csCollectionGroupName, pItem->iDataSymbol);
			add_log_message(tmProjectItemString);

            IDataFactory* pOutputDataFactory = 
				pConverter->GetDataFile()->GetOutputSymbol(pItem->iDataSymbol);
			if (!pOutputDataFactory)
			{
                add_log_message(" FAILED! Wrong data symbol index specified.");			
				continue;
			}

			CCollectionGroup* pGroup = 
				pConverter->GetDataCollection()->GetGroupByName(pItem->csCollectionGroupName);
			if (!pGroup)
			{
                add_log_message(" FAILED! Wrong collection group name specified.");			
				continue;
			}	

			add_log_message(" Enumerating data group items and building data file content...");

			pGroup->GetDataArray()->CreateEnumerator();
			while (CCollectionDataItem* pItem = pGroup->GetDataArray()->GetNextItem())
			{
				CString tmGroupItem = 
					CString("  Processing file \"") + pItem->GetFileName() + CString("\"...");
				add_log_message(tmGroupItem);

				IDataFactory* pInputDataFactory = 
					CCollectionConverterOperation_LoadImage::LoadImage(
						pItem->GetFileName());
				if (!pInputDataFactory)
				{
					add_log_message("  FAILED! Wrong file format.");
					continue;
				}

				if (pInputDataFactory->GetDataLength() != SymbolDimension)
				{
					add_log_message("  FAILED! Wrong data image length detected after bitmap converting.");
					
					pInputDataFactory->ReleaseFactory();
					delete pInputDataFactory;

					continue;
				}

				add_log_message("  Adding symbols to data file...");

				mDataFile.AddInputSymbol(pInputDataFactory);
				mDataFile.AddOutputSymbol(pOutputDataFactory);

				pInputDataFactory->ReleaseFactory();
				delete pInputDataFactory;

				add_log_message("  Processing file finished.");			
			}		
		
			add_log_message(" Converting current project item finished.");
		}	
	
		add_log_message("Saving data file to disk...");

		if (!mDataFile.SaveToFile(FileName))
		{
			add_log_message("FAILED! File could not be saved.");
			return false;
		}	
	
		return true;
	}
};