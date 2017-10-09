#pragma once

#include "System\Directory.h"

#include "ZipUtils\unzip.h"

class CProcessExport
{
public:
	static bool ExportSolution(
		CExportSolution* pExportSolution,
		CString DestinationFolder,
		ILogProvider* pLogProvider)
	{	
		pLogProvider->AddLogMessage(CString(_T("")), 
			CString(_T("Exporting solution...")), CString(_T("")));

		pExportSolution->CreateEnumerator();
		while (CExportGroup* pExportGroup = pExportSolution->GetNextGroup())
		{
			CString tmMessage = 
				CString(_T(" Processing group: ")) + 
				pExportGroup->csGroupName + 
				CString(_T("..."));
			pLogProvider->AddLogMessage(CString(_T("")), 
				tmMessage, CString(_T("")));

			if (pExportGroup->csGroupFolder != _T(""))
			{
				// Creating folder for the current group
				CString tmFolderPath = 
					DestinationFolder + 
					CString(_T("\\")) + 
					pExportGroup->csGroupFolder;

                CreateDirectory(tmFolderPath, NULL);			
			}

			pExportGroup->CreateEnumerator();
			while (CExportItem* pExportItem = pExportGroup->GetNextItem())
			{			
				CString tmMessage = 
					CString(_T("  Processing item: ")) + 
					pExportItem->csItemName;
				pLogProvider->AddLogMessage(CString(_T("")), 
					tmMessage, CString(_T("")));

				CString csFileName;
				if (pExportItem->csItemType == _T("project"))
					csFileName = pExportItem->csItemName;
				else
					csFileName = 
						pExportSolution->csAppFolder +
						CString("\\") + 
						pExportItem->csItemPathPrefix + 
						pExportItem->csItemName;

				if (pExportItem->csItemType == _T("compressed"))
				{
					CString tmDestinationFolder = 
						DestinationFolder + 
						CString(_T("\\")) + 
						pExportGroup->csGroupFolder; + 
						CString(_T("\\"));

					// Unzip compressed file
					HZIP hz = OpenZip(csFileName, NULL);
					SetUnzipBaseDir(hz, tmDestinationFolder);
					ZIPENTRY ze; 
					GetZipItem(hz, -1, &ze); 
					int numitems = ze.index;
					for (int zi = 0; zi < numitems; zi++)
					{
						if (strlen(ze.name) > 0)
						{
							CString tmMessage = 
								CString("   Uncompressed item: ") + 
								CString(_T(ze.name));
							pLogProvider->AddLogMessage(CString(_T("")), 
								tmMessage, CString(_T("")));
						}

						GetZipItem(hz, zi, &ze);
                        UnzipItem(hz,zi,ze.name);
					}
					CloseZip(hz);
				} else
				{
					// Just copy current item to the specified location
					CString tmNewFileName = 
						DestinationFolder + 
						CString(_T("\\")) + 
						pExportGroup->csGroupFolder + 
						CString(_T("\\")) + 
						CPath::GetFileName(csFileName);

					CopyFile(csFileName, tmNewFileName, FALSE);
				}
			}
		}

		pLogProvider->AddLogMessage(CString(_T("")), 
			CString(_T("Solution has been exported successfully.")), CString(_T("")));
		
		return true;
	}
};