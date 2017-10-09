#pragma once

#ifndef SOURCE_NEUROFACTORY_EXTERNAL
#define SOURCE_NEUROFACTORY_INTERNAL
#endif

#include "CmnFactory.h"

class CNeuroFactory : 
	public IElementsCollection, 
	public INetworkProcessor,
	public INetworkVerifier,
	public IStorageController
{
public:
	CNeuroFactory(void);
	~CNeuroFactory(void);

	// Common elements processing functions
#ifdef SOURCE_NEUROFACTORY_INTERNAL
	void			AddElement(IElement* pElement);
	void			ReleaseElementsList();

	void			RemoveConnections(IElement* pElement);

	CConnection*	FindConnectionByPrevPtr(CConnection* pConnection);
#endif
	
// IElementsCollection declarations section
public:
#ifdef SOURCE_NEUROFACTORY_INTERNAL
	virtual void			RemoveElement(IElement* pElement);

	virtual void			SelectElement(IElement* pElement, bool bShift, bool bCtrl);
#endif

	virtual int				GetInputsCount();
	virtual int				GetOutputsCount();

	ENUMERATOR(mNetworkElements, IElement*, CreateElementsEnumerator, GetNextElement, posElementsEnum)

// INetworkVerifier declarations section
	virtual void			VerifyNetwork(int& ErrorsCount, int& WarningsCount, 
		ILogProvider* pLogProvider = NULL);

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

};
