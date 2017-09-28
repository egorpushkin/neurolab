#pragma once

#include "CmnTrainers.h"

typedef ITrainer* (*PCREATE_TRAINER_INSTANCE_ROUTINE)();
typedef void (*PRELEASE_TRAINER_INSTANCE_ROUTINE)(ITrainer* pTrainer);

class CTrainerInstance
{
public:
	CTrainerInstance(CString& FileName);
	~CTrainerInstance(void);

	bool			CreateTrainerInstance();
	void			ReleaseTrainerInstance();

	CString			csTrainerFileName;

	ITrainer*		pTrainer;

private:
	HMODULE			hLibrary;

	PCREATE_TRAINER_INSTANCE_ROUTINE	pfnCreateTrainerInstance;
	PRELEASE_TRAINER_INSTANCE_ROUTINE	pfnReleaseTrainerInstance;
};
