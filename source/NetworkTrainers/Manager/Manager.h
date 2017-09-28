#pragma once

#include "CmnManager.h"

#include "..\Trainers\TrainersManager.h"

class CManager : public IManagerControl
{
public:
	CManager(void);
	~CManager(void);

// IManagerControl declarations section
public:
	virtual BOOL			InitializeManagerInstance();
	virtual BOOL			ReleaseManagerInstance();
	virtual void			SetAppFolder(CString& csFolder);

	virtual void			SetAppController(IAppController* pController);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	CString					csAppFolder;

	IAppController*			pAppController;

	CTrainersManager		mTrainersContainer;
};