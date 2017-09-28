#pragma once

#include "CmnTrainers.h"

#include "TrainerInstance.h"

class CTrainersManager :
	public ITrainersContainer
{
public:
	CTrainersManager(void);
	~CTrainersManager(void);

	void				SetAppFolder(CString& csFolder);

	void				CreateContainer();
	void				ReleaseContainer();	

	void				LoadInstalledTrainers();
	void				AddTrainer(CString& csPluginFilePath, CString& csPluginFileName);
	

// ITrainersContainer declarations section
public:
	ENUMERATOR(mTrainers, ITrainer*, CreateEnumerator, GetNextTrainer, posTrainersEnum)

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	CList<CTrainerInstance*, CTrainerInstance*>	mTrainerInstances;
	CList<ITrainer*, ITrainer*>					mTrainers;

	CString					csAppFolder;
};
