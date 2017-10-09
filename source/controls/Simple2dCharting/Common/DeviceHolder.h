#ifndef DEVICEHOLDER_H__S2DCHARTING__INCLUDED_
#define DEVICEHOLDER_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	class DeviceHolder
	{
	public:

		DeviceHolder(BasicDeviceRef device_, void* pWnd, void* pHandle);
		virtual ~DeviceHolder();

	private:

		BasicDevicePtr device_; 

	}; // DeviceHolder

} // Simple2dCharting

#endif // !DEVICEHOLDER_H__S2DCHARTING__INCLUDED_
