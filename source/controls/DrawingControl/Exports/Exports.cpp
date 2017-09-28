#include "Common/stdafx.h"

#include "UI/ControlHolder.h"

DrawingControl::IControlHolder* InstantiateControl()
{
	DrawingControl::ControlHolder* pControl = new DrawingControl::ControlHolder;
	
	DrawingControl::IControlHolder* piControl = NULL;
	result r = pControl->QueryInterface(DrawingControl::IID_IControlHolder, (void**)&piControl);

	return ( SUCCEEDED(r) ) ? ( piControl ) : ( NULL );
}
