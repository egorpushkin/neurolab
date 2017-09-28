#include "StdAfx.h"
#include "GlobalStorage.h"

// Global Environment
CString				CLuaStorage_GlobalEnvironment::csCurrentDirectory	= _T("");

CString				CLuaStorage_GlobalEnvironment::csSolutionDirectory	= _T("");
CString				CLuaStorage_GlobalEnvironment::csScriptDirectory	= _T("");
CString				CLuaStorage_GlobalEnvironment::csAppDirectory		= _T("");

// Lop Package
ILogProvider*		CLuaStorage_LogProvider::pLogProvider		= NULL;
int					CLuaStorage_LogProvider::iCurPercentage		= 0;

// Global Solution information
CScriptSolution*			CLuaStorage_Solution::pSolution					= NULL;
CImportManagerComponent*	CLuaStorage_Solution::pImportManagerComponent	 = NULL;	

CList<CLuaStorage_DataFile*, CLuaStorage_DataFile*>	CLuaStorage_Solution::mDataFiles;
CList<CLuaStorage_Bitmap*, CLuaStorage_Bitmap*>		CLuaStorage_Solution::mBitmapFiles;
CList<CLuaStorage_Project*, CLuaStorage_Project*>	CLuaStorage_Solution::mProjectFiles;

// NeuroLabEnv Control Interfaces
INetworkProcessor*	CLuaStorage_NetworkProcessor::pNetworkProcessor = NULL;
IElementsCollection* CLuaStorage_NetworkProcessor::pElementsCollection = NULL;

// Data objects Garbage Collector
CList<IDataFactory*, IDataFactory*> CLuaStorage_FactoriesContainer::mObjectsList;
CList<IDataFile*, IDataFile*> CLuaStorage_DataFilesContainer::mObjectsList;
CList<IDataBitmap*, IDataBitmap*> CLuaStorage_BitmapsContainer::mObjectsList;
CList<CChartsViewDlg*, CChartsViewDlg*> CLuaStorage_ChartsContainer::mObjectsList;
