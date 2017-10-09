#include "stdafx.h"
#include "DisplayMngThread.h"

#include "../../../ScriptEnv.h"
#include "../ui/ChartsViewDlg.h"

#include "DataBuffer.h"

DWORD WINAPI DisplayMngThread(PVOID param)
{
	DataBuffer* pBuffer = (DataBuffer*)param;

	pBuffer->pChartsView_ = new CChartsViewDlg(pBuffer->name_);

	CChartsViewDlg* pChartsView = pBuffer->pChartsView_;

	SetEvent(pBuffer->event_);

	pChartsView->DoModal();
 
	return 0;
}
