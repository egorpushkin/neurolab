#include "Includes.h"

#include "BasicDevice.h"

#include "DeviceHolder.h"

namespace Simple2dCharting
{

	DeviceHolder::DeviceHolder(BasicDeviceRef device, void* pWnd, void* pHandle)
		: device_(device)
	{
		device_->ConstructFromHandle(pWnd, pHandle);
	}
	
	DeviceHolder::~DeviceHolder()
	{
		device_->DumpContext();
	}

} // Simple2dCharting