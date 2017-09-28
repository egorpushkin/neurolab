#include "stdafx.h"

#include "../Common/Includes.h"

#include "ManagerThread.h"

#include "Manager.h"

namespace Drawing
{

	DWORD WINAPI ManagerThread(PVOID param)
	{
		// Acquiring manager passed as parameter
		Manager* pManager = (Manager*)param;

		// Get control object
		DrawingControl::IControlHolderPtr controlHolder = pManager->GetControl();

		// Notify script on successful initialization
		pManager->StopWaiting();

		// Note! pManager is not accessible any more after StopWaiting return

		// Display control synchronously
		controlHolder->DisplayControl();

		return 0;
	}

}
