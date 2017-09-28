#pragma once

#include "CmnElement.h"
#include "CmnLog.h"

#include "Templates\Enumerator.h"

interface INetworkProcessor : public IObject
{
	virtual void			ProcessNetwork() = 0;

	virtual void			SetInputData(IDataFactory* pData) = 0;
	virtual void			SetOutputData(IDataFactory* pData) = 0;

	virtual void			GetInputData(IDataFactory* pData) = 0;
	virtual void			GetOutputData(IDataFactory* pData) = 0;
};

interface IElementsCollection : public IObject
{
	virtual void			RemoveElement(IElement* pElement) = 0;

	virtual void			SelectElement(IElement* pElement, bool bShift, bool bCtrl) = 0;

	virtual int				GetInputsCount() = 0;
	virtual int				GetOutputsCount() = 0;

	INTERFACE_ENUMERATOR_DECLARATION(IElement*, CreateElementsEnumerator, GetNextElement)
};

interface INetworkVerifier : public IObject
{
	virtual void			VerifyNetwork(int& ErrorsCount, int& WarningsCount, 
		ILogProvider* pLogProvider = NULL) = 0;
};