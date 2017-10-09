#pragma once

#include "CmnTrainers.h"

#include "RBFTrainingAlg.h"

class CRBFTrainer : 
	public ITrainer
{
public:
	CRBFTrainer(void);
	~CRBFTrainer(void);

// ITrainer declarations section
	// Receiving information 
	virtual void			GetTrainerInfo(TRAINER_INFO* pTrainerInfo);
	virtual bool			IsSupportDataType(int DataType);

	// Compalsory initialization
	virtual void			SetDataTypeForTraining(int DataType);
	virtual void			SetLogProvider(ILogProvider* pLog);

	// Initialization with data for training
	virtual void			SetDataFile(IDataFile* pData);

	// Initialozation with method dependent data
	virtual void			SetElementsFactory(IElementsCollection* pCollection);

	// Trainer operations
	virtual void			StartTraining();
	virtual void			Configure();

	virtual void			PauseTrainng();
	virtual void			ResumeTrainng();
	virtual void			StopTrainng();

	// Training benchmark information
	virtual int				GetTotalProcessed();

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	IElementsCollection*	pElementsCollection;
	IDataFile*				pDataFile;

	int						iTrainingDataType;

	ILogProvider*			pLogProvider;

	CRBFTrainingAlg			mRBFTrainingAlg;
};
