#pragma once

#include "Templates\Enumerator.h"

#include "CmnObjects.h"
#include "CmnStorage.h"
#include "CmnOutput.h"
#include "CmnFunction.h"
#include "CmnConnection.h"

#include "DefElement.h"

struct sElement
{
	sElement(CString& Name, CString& Title)
	{
		csName = Name;
		csTitle = Title;
	}

	CString					csName;
	CString					csTitle;
};

interface IBuilderControl;

interface IElement : public IObject
{
	virtual void			CommandNotify(WPARAM wParam, LPARAM lParam) = 0;
	
	virtual void			SetElementID(int iID) = 0;
	virtual int				GetElementID() = 0;

	virtual CString			GetElementTitle() = 0;

	virtual	int				GetElementType() = 0;

	virtual void			SetSysName(CString& Name) = 0;
	virtual CString			GetSysName() = 0;
	virtual void			SetSysTitle(CString& Title) = 0;
};

interface IBuilderElement : public IObject
{
	virtual void			SetOutputControl(IBuilderControl* pControl) = 0;
	virtual IBuilderControl*	GetOutputControl() = 0;

	virtual void			SetElementPosition(CPoint& point) = 0;
	virtual CPoint			GetElementPosition() = 0;

	virtual void			ShowElement() = 0;
	
	virtual bool			IsClicked(CPoint& point) = 0;
	
	virtual void			SelectElement(bool bSelect) = 0;
	virtual bool			IsSelected() = 0;

	virtual void			TrackPopupMenu(CPoint& point) = 0;

	virtual CPoint			GetPositionForConnectedElement(CConnection* pConnection) = 0;
};

interface IDataFlow : public IObject
{
	virtual sFunction*		GetElementFunction() = 0;
	virtual void			SetElementFunction(sFunction* pFunction) = 0;
	virtual CString			GetFunctionName() = 0;

	virtual bool			RequireData() = 0;

	// Data flow operations
	virtual void			SetWaitDataState() = 0;

	// Processing network operations
	virtual bool			IsReadyForProcessing() = 0;
	virtual void			FlowData() = 0;
	virtual void			ProcessElement() = 0;

	// Training network operations
	virtual bool			IsReadyForTraining() = 0;
	virtual void			BackFlow() = 0;
	
	// Element data operations
	virtual void			GetElementData(IDataFactory* pData) = 0;
	virtual void			SetElementData(IDataFactory* pData) = 0;
	virtual IDataFactory*	GetDataFactory() = 0;			

	virtual void			SplitConnectionsData(IDataFactory* pData, int FactoryType) = 0;
};

interface IConnectionsFactory : public IObject
{
	virtual void			RemoveConnections() = 0;
	
	virtual void			AddConnection(CConnection* pConnection) = 0;
	virtual void			RemoveConnection(CConnection* pConnection) = 0;

	virtual	bool			MoveConnection(CConnection* pConnection, bool bIsMoveUp = false) = 0;

	virtual int				GetConnectionsCount() = 0;
	INTERFACE_ENUMERATOR_DECLARATION(CConnection*, CreateEnumerator, GetNextConnection)	
};

interface IDataConnector : public IObject
{
	virtual void			AddConnectionTo(IElement* pElement, int FactoryType) = 0;
	virtual void			RemoveConnection(CConnection* pConnection) = 0;

	virtual	void			SetAddConnectionState(int iState, int Count) = 0;
	virtual void			ProcessAddConnection(IElement* pElement) = 0;

	virtual	bool			MoveConnection(CConnection* pConnection, bool bIsMoveUp = false) = 0;

	virtual IConnectionsFactory* GetConnectionsFactory(int FactoryType) = 0;

	virtual	CConnection*	FindConnectionByPrevPtr(CConnection* pConnection) = 0;
};

interface ILayerControl : public IObject
{
	virtual void			SetInputData(IDataFactory* pData) = 0;
	virtual void			SetOutputData(IDataFactory* pData) = 0;

	virtual bool			ModifyWeights() = 0;
	virtual void			ResetWeights(float Value) = 0;

	virtual void			CreateWeights(int Inputs, int Dimension) = 0;
	virtual void			RemoveWeights() = 0;

	virtual int				GetDimension() = 0;
	virtual int				GetInputsCount() = 0;

	virtual float			GetWeight(int i, int j) = 0;
	virtual void			SetWeight(int i, int j, float fWeight) = 0;

	virtual void			SetDelta(int i, float Value) = 0;
	virtual float			GetDelta(int i) = 0;
};