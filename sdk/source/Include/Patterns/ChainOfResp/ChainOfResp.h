#ifndef CHAINOFRESP_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define CHAINOFRESP_H__CHAINOFRESP__COMMONKIT__INCLUDED_

namespace ChainOfResp
{

	#include "Interfaces/IChainNode.h"
	#include "Interfaces/INodeDataReceiver.h"
	#include "Interfaces/INodeDataTransmitter.h"
	#include "Interfaces/IChainProcessor.h"
    
	#include "Processor/ChainProcessor.h"

	#include "Model/ChainNodeImpl.h"
	#include "Model/SetInputData.h"
	#include "Model/GetOutputData.h"
	#include "Model/AddNode.h"
	#include "Model/CreateProcessor.h"

}

#endif // !CHAINOFRESP_H__CHAINOFRESP__COMMONKIT__INCLUDED_
