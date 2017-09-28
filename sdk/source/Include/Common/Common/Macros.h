#ifndef MACROS_H__MINCOM__COMMONKIT__INCLUDED_
#define MACROS_H__MINCOM__COMMONKIT__INCLUDED_

// Regular QueryInterface replacement
//////////////////////////////////////////////////////////////////////////

// Support for xImpl paradigm
//////////////////////////////////////////////////////////////////////////
#define BEGIN_LOCAL_QI_MAP()											\
	virtual result LocalQueryInterface(REFIID iid, void** ppObject)		\
	{																	\
		*ppObject = NULL;

#define DECLARE_IMPL_CLASS(impl_class)									\
	if (SUCCEEDED(impl_class::QueryInterface(iid, ppObject)))			\
		return S_OK;

#define END_LOCAL_QI_MAP()												\
		return E_NOTIMPL;												\
	}

#define LOCAL_QI(iid, ppObject)											\
	*ppObject = NULL;													\
	if (SUCCEEDED(LocalQueryInterface(iid, ppObject)))					\
		return S_OK;

#define DECLARE_IID(interface_type, interface_iid)						\
	if (iid == interface_iid)											\
	{																	\
		*ppObject = static_cast< interface_type* >(this);				\
		MinCOM::CommonImpl< interface_type >::GetCommon()->AddRef();	\
		return S_OK;													\
	}

#define DECLARE_COMMON(iid_val)											\
	if (iid == MinCOM::IID_ICommon)										\
	{																	\
		*ppObject = MinCOM::CommonImpl< iid_val >::GetCommon();			\
		MinCOM::CommonImpl< iid_val >::GetCommon()->AddRef();			\
		return S_OK;													\
	}

// Support for casual QuieryInterface methods standardization
//////////////////////////////////////////////////////////////////////////
#define CHECK_FOR_IID(iid_var, ppObject_var, interface_type, iid)		\
	if (iid_var == iid)													\
	{																	\
		*ppObject_var = static_cast< interface_type* >(this);			\
		MinCOM::CommonImpl< interface_type >::GetCommon()->AddRef();	\
		return S_OK;													\
	}

#define QUERY_COMMON(iid_var, ppObject_var, iid)						\
	if (iid_var == MinCOM::IID_ICommon)									\
	{																	\
		*ppObject_var = MinCOM::CommonImpl< iid >::GetCommon();			\
		MinCOM::CommonImpl< iid >::GetCommon()->AddRef();				\
		return S_OK;													\
	}


#endif // !MACROS_H__MINCOM__COMMONKIT__INCLUDED_
