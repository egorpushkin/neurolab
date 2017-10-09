#pragma once

#include "CmnTrainers.h"

#define	M_JACOBI				0x00000001
#define	M_HOUSEHOLDER			0x00000002

struct sPCASettings
{
	sPCASettings()
		: iFeaturesCount(64)
		, iMethod(M_JACOBI)
	{
	}

	int			iFeaturesCount;
	int			iMethod;
};

#include "PCALogic/TrainingTool.h"

class CPCATrainerImpl : 
	public ITrainer
{
public:
	CPCATrainerImpl(void);
	~CPCATrainerImpl(void);

// Custom functions
	bool				VerifyWhetherTrainingAvaliable();

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
	sPCASettings			mSettings;

	IElementsCollection*	pElementsCollection;
	IDataFile*				pDataFile;

	int						iTrainingDataType;

	ILogProvider*			pLogProvider;

	CTrainingTool			mTrainingTool;
};
