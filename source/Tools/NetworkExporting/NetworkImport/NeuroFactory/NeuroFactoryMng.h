#pragma once

#include "CmnFactory.h"
#include "..\..\..\..\BuilderElements\Containers\ElementsCore.h"

class CNeuroFactoryMng :
	public IElementsCollection, 
	public INetworkProcessor,
	public IStorageController
{
public:
	CNeuroFactoryMng(void);
	~CNeuroFactoryMng(void);

	CConnection*		FindConnectionByPrevPtr(CConnection* pConnection);
	void				RemoveConnections(IElement* pElement);
	void				ReleaseElementsList();

	void				SetBuilderElementsObjects(
		IGroupsContainer* pGroups,
		IFunctionsFactory* pFunctions);
    
// IElementsCollection declarations section
public:
	virtual void			RemoveElement(IElement* pElement);
	virtual void			SelectElement(IElement* pElement, bool bShift, bool bCtrl);

	virtual int				GetInputsCount();
	virtual int				GetOutputsCount();

	ENUMERATOR(mNetworkElements, IElement*, CreateElementsEnumerator, GetNextElement, posElementsEnum)

// INetworkProcessor declarations section
	virtual void			ProcessNetwork();

	virtual void			SetInputData(IDataFactory* pDataFactory);
	virtual void			SetOutputData(IDataFactory* pDataFactory);

	virtual void			GetInputData(IDataFactory* pDataFactory);
	virtual void			GetOutputData(IDataFactory* pDataFactory);

// IStorageController declarations section
	virtual bool			Serialize(CArchive& ar);

// IObject declarations section
	virtual CString			GetClassString();
	virtual void			QueryInterface(int iIDD, void** ppvObject);

private:
	CList<IElement*, IElement*>	mNetworkElements;

	IGroupsContainer* pGroupsContainer;
	IFunctionsFactory* pFunctionsFactory;
};