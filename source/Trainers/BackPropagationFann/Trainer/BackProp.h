#pragma once

#include "CmnTrainers.h"

#include "fann.h"

#define WIM_NOINIT				0x00
#define WIM_RANDOM				0x01
#define WIM_CONSTANT			0x02
#define WIM_ADOPTIVE			0x03

#define NSA_AUTOMATIC			0x00
#define NSA_CUSTOM				0x01

struct sBPSettings
{
	sBPSettings()
		: fHiddenTrainSpeed(0.7f)

		, fMaxError(0.01f)
		, iMaxLoopsCount(100000)

		, iWeightsInitMethod(WIM_ADOPTIVE)

		, fStartRange(-1.0f)
		, fEndRange(1.0f)
		, fConstant(0.1f)

		, iTrainingMethod(FANN_TRAIN_INCREMENTAL)

		, iNetStruct(NSA_CUSTOM)
		
		, iHiddenActivation(FANN_SIGMOID_SYMMETRIC)
		, iOutputActivation(FANN_SIGMOID)
	{
	}

	float				fHiddenTrainSpeed;

	float				fMaxError;
	int					iMaxLoopsCount;

	int					iWeightsInitMethod;

	float				fStartRange;
	float				fEndRange;
	float				fConstant;

	int					iTrainingMethod;

	int					iNetStruct;

	unsigned int		iHiddenActivation;
	unsigned int		iOutputActivation;
};

//#include "BackPropAlg.h"

class CBackProp : 
	public ITrainer
{
public:
	CBackProp(void);
	~CBackProp(void);

// Custom functions
	bool				VerifyDataFile();

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
	ILogProvider*			pLogProvider;

	GenericNetwork			network_;
};
