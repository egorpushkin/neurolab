#pragma once

#include "CmnObjects.h"

interface ILogProvider : public IObject
{
	virtual void			ClearLog() = 0;
	virtual void			AddLogMessage(CString& MessageType, CString& Message, CString& MessageSection) = 0;
};