#pragma once

#include "CmnObjects.h"

interface IScriptingElementControl : public IObject
{
	virtual int				GetDimensionSE() = 0;
	virtual int				GetInputsCountSE() = 0;

	virtual void			CreateWeightsSE(int Inputs, int Dimension) = 0;
	virtual void			RemoveWeightsSE() = 0;

	virtual void			SetScriptString(CString& ScriptSrting) = 0;
	virtual CString			GetScriptString() = 0;
};