#pragma once

#include "Templates\Enumerator.h"
#include "CmnObjects.h"
#include "CmnDataFile.h"
#include "CmnFactory.h"
#include "CmnLog.h"

#include "DefTrainers.h"

struct TRAINER_INFO
{
	CString			csTrainerName;
	CString			csTrainerVersion;
};

interface ITrainer : public IObject
{
	// Receiving information 
	virtual void			GetTrainerInfo(TRAINER_INFO* pTrainerInfo) = 0;
	virtual bool			IsSupportDataType(int DataType) = 0;

	// Compalsory initialization
	virtual void			SetDataTypeForTraining(int DataType) = 0;
	virtual void			SetLogProvider(ILogProvider* pLog) = 0;

	// Initialization with data for training
	virtual void			SetDataFile(IDataFile* pData) = 0;

	// Initialozation with method dependent data
	virtual void			SetElementsFactory(IElementsCollection* pCollection) = 0;

	// Trainer operations
	virtual void			StartTraining() = 0;
	virtual void			Configure() = 0;

	virtual void			PauseTrainng() = 0;
	virtual void			ResumeTrainng() = 0;
	virtual void			StopTrainng() = 0;

	// Training benchmark information
	virtual int				GetTotalProcessed() = 0;
};

interface ITrainersContainer : public IObject
{
	INTERFACE_ENUMERATOR_DECLARATION(ITrainer*, CreateEnumerator, GetNextTrainer)	
};