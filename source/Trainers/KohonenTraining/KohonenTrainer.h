#pragma once

#include "CmnTrainers.h"

struct sSettings
{
	sSettings()
	{
		bNormilizeInputs = true;

		bInitializeWeights = true;
		fFromValue = -1;
		fToValue = 1;
		bNormilizeWeights = true;

		fMaxDistance = 0.1;
		iLoopsCount = 1000;

		fStartSpeed = 0.7f;
		fMultiplier = 0.9f;
	}
    
	bool			bNormilizeInputs;
	
	bool			bInitializeWeights;
	float			fFromValue;
	float			fToValue;
	bool			bNormilizeWeights;

	float			fMaxDistance;
	int				iLoopsCount;

	float			fStartSpeed;
	float			fMultiplier;
};

#include "KohonenTrainingAlg.h"

class CKohonenTrainer :
	public ITrainer
{
public:
	CKohonenTrainer(void);
	~CKohonenTrainer(void);

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

	CKohonenTrainingAlg		mKohonenTrainingAlg;

	sSettings				mSettings;
};
