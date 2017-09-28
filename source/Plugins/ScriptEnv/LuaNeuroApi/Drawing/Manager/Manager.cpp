#include "stdafx.h"

#include "../Common/Includes.h"

#include "Manager.h"

#include "ManagerThread.h"

#include "CmnDecl.h"

#include "Callback.h"

// Drawing control imports
//////////////////////////////////////////////////////////////////////////
__declspec(dllimport) DrawingControl::IControlHolder* InstantiateControl();
//////////////////////////////////////////////////////////////////////////

namespace Drawing
{

	Manager::Manager(lua_State* L)
		: event_(NULL)
		, L_(L)
		, controlHolder_()
	{
	}

	DrawingControl::IControlHolderPtr Manager::DisplayControl()
	{
		// Initialize signaler
		event_ = ::CreateEvent(NULL, TRUE, FALSE, NULL);

		// Execute thread
        __beginthreadex(NULL, 0, ManagerThread, this, 0, NULL); 
	
		// Wait while thread perform all necessary initialization before displaying control
		::WaitForSingleObject(event_, INFINITE);
		::CloseHandle(event_);
		event_ = NULL;

		return controlHolder_;
	}

	void Manager::StopWaiting()
	{
		// Notify launcher on initialization success
		SetEvent(event_);
	}

	DrawingControl::IControlHolderPtr Manager::GetControl()
	{
		if ( !controlHolder_ )
		{
			// Instantiate remote object
			controlHolder_ = InstantiateControl();

			// Setup callback interface
			DrawingControl::IEventsPtr eventsCallback(
				new Callback(controlHolder_, L_), DrawingControl::IID_IEvents	
			);

			controlHolder_->GetDrawingControl()->SetEventsHandler(GetImpl(eventsCallback));
		}

		// Return created object
		return controlHolder_;
	}

}
