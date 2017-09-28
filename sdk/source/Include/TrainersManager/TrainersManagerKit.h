//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: TrainersManagerKit.h
//	Description: Trainers Manager SDK main include file.   

//	Include this file in your solution to add functionality of this SDK.

#ifndef TRAINERSMANAGERKIT_H__TRAINERSMANAGER__INCLUDED_
#define TRAINERSMANAGERKIT_H__TRAINERSMANAGER__INCLUDED_

#include "ExternalIncludes.h"

namespace TrainersManagerKit
{
	
	#include "Common/ErrorCodes.h"
	#include "Common/TrainerInformation.h"
	#include "Common/Properties.h"
	#include "Common/Log.h"
	#include "Common/Loaders.h"

	#include "Identifiers/CLSID.h"
	#include "Identifiers/PID.h"

	#include "Interfaces/ILogProvider.h"
	#include "Interfaces/ITextLogProvider.h"
	#include "Interfaces/IChartLogProvider.h"
	#include "Interfaces/IExecutionStateLog.h"

	#include "Interfaces/IProperties.h"
	#include "Interfaces/IGeneralProcessor.h"
	#include "Interfaces/ITrainer.h"
	
	#include "Interfaces/ITrainersLoader.h"	
	#include "Interfaces/ITrainersManager.h"
	
	#include "Interfaces/IID.h"
	
	#include "Model/Definitions/TrainerImplTypes.h"
	#include "Model/Helpers/Enumerators.h"
	#include "Model/TrainerImpl.h"
	#include "Model/PropertiesImpl.h"
	#include "Model/GeneralProcessorImpl.h"
	#include "Model/ExecutionStateLogImpl.h"

	#include "Helpers/AddTextMessage.h"

}

namespace TrMngKit = TrainersManagerKit;

#endif // !TRAINERSMANAGERKIT_H__TRAINERSMANAGER__INCLUDED_
