#ifndef FIND_H__CONTAINER__COMMONKIT__INCLUDED_
#define FIND_H__CONTAINER__COMMONKIT__INCLUDED_

template
<
	class T
>
bool find(const MinCOM::ComPtr< IEnumerator<T> >& enumerator, const T& val)
{
	for (bool hasElement = enumerator->SelectFirst(); hasElement; hasElement = enumerator->SelectNext())
	{
        if ( enumerator->GetSelected() == val )
			return true;
	}
	return false;
}
	
#endif // !FIND_H__CONTAINER__COMMONKIT__INCLUDED_
