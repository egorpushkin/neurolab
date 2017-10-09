#include "Includes.h"

#include "Cartesian/Cartesian.h"

#include "BasicDevice.h"

#include "BasicChart.h"

#include "BasicLocator.h"

#include "BasicRenderer.h"

namespace Simple2dCharting
{

	BasicRenderer::BasicRenderer()
		: device_()
	{
	}

	BasicRenderer::~BasicRenderer()
	{
	}

	// Public interface
	void BasicRenderer::SetDevice(BasicDeviceRef device)
	{
		device_ = device;
	}

} // Simple2dCharting

