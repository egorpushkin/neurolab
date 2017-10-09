#pragma once

#include "CmnTrainers.h"

#define	VCT_INCREMENT			0x01
#define	VCT_MULTIPLY			0x02

#define WIT_RANDOM				0x01
#define WIT_CONSTANT			0x02

struct sBPSettings
{
	sBPSettings()
	{
		fOutputTrainSpeed = 1.0f;
		fHiddenTrainSpeed = 1.0f;

		iOutputSpeedChange = VCT_MULTIPLY;
		iHiddenSpeedChange = VCT_MULTIPLY;

		fOutputChange = 1.1f;
		fHiddenChange = 1.1f;

		bSelectRandomSymbolForTraining = false;

		fMaxError = 0.1f;
		iMaxLoopsCount = 10000;

		bSaveNeuronWeights = true;	

		bInitializeWeights = true;
		iWeightsInitializationType = WIT_RANDOM;

		fStartRange = -1.0f;
		fEndRange = 1.0f;
		fConstant = 0.1f;
	}

	float				fOutputTrainSpeed;
	float				fHiddenTrainSpeed;

	int					iOutputSpeedChange;
	int					iHiddenSpeedChange;

	float				fOutputChange;
	float				fHiddenChange;

	bool				bSelectRandomSymbolForTraining;

	float				fMaxError;
	int					iMaxLoopsCount;

	bool				bSaveNeuronWeights;

	bool				bInitializeWeights;
	int					iWeightsInitializationType;

	float				fStartRange;
	float				fEndRange;
	float				fConstant;
};

#include "BackPropAlg.h"

class CBackProp : 
	public ITrainer
{
public:
	CBackProp(void);
	~CBackProp(void);

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
	sBPSettings				mSettings;

	IElementsCollection*	pElementsCollection;
	IDataFile*				pDataFile;

	int						iTrainingDataType;

	ILogProvider*			pLogProvider;

	CBackPropAlg			mAlgRealization;
};
