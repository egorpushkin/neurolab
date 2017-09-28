#ifndef QUERYTOOL_H__COMMON__INCLUDED_
#define QUERYTOOL_H__COMMON__INCLUDED_

template
<
	class U
>
class AssertOnError
{
public:
	static result VerifyResult(result resultCode, U* piObject)
	{
		assert(resultCode == S_OK);
		assert(piObject != NULL);	

		// Do it to avoid 'warning C4100' in release mode
		resultCode = S_OK;
		piObject = NULL;

		return S_OK;
	}
};

template
<
	class U
>
class DoNothingOnError
{
public:
	static result VerifyResult(result /* resultCode */, U* /* piObject */)
	{
		// No action is being performed
		return S_OK;
	}
};

template
<
	class T,
	class U,
	template <class> class AssertionPolicy = AssertOnError
>
class QueryTool
	: public AssertionPolicy<U>
{
public:
	static U* QueryInterface(T* pObject, REFIID iid)
	{
		U* piObject = NULL;
		result resultCode = pObject->QueryInterface(iid, (void**)&piObject);
		
		// All verifications would be performed in debug mode only
		assert(AssertionPolicy<U>::VerifyResult(resultCode, piObject) == S_OK);

		// Do it to avoid 'warning C4100' in release mode
		resultCode = S_OK;

		return piObject;
	}
};

#endif // !QUERYTOOL_H__COMMON__INCLUDED_
