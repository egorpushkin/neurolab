#pragma once

#define clear_log()														\
	if (pLogProvider)													\
		pLogProvider->ClearLog();

#define add_log_message(type, message, section)							\
	if (pLogProvider)													\
		pLogProvider->AddLogMessage(									\
			CString(_T(type)),											\
			CString(_T(message)),										\
			CString(_T(section)));

#define	verifier_routine(routine_name)									\
	routine_name(ErrorsCount,											\
		WarningsCount,													\
		pElementsCollection,											\
		pLogProvider);	

#define verifier_routine_impl(routine_name)								\
	static void routine_name(											\
		int& ErrorsCount,												\
		int& WarningsCount,												\
		IElementsCollection* pElementsCollection,						\
		ILogProvider* pLogProvider = NULL)

#define enumerate_elements()											\
	pElementsCollection->CreateElementsEnumerator(3);					\
	while (IElement* pElement = pElementsCollection->GetNextElement(3))




