#ifndef FOREACH_H__CONTAINER__COMMONKIT__INCLUDED_
#define FOREACH_H__CONTAINER__COMMONKIT__INCLUDED_

template
<
	class T,
	class Function
>
Function for_each(IEnumerator<T>* piEnum, Function func)
{
	for (bool hasElement = piEnum->SelectFirst(); hasElement; hasElement = piEnum->SelectNext())
        func(piEnum->GetSelected());

	return (func);
}
	
#endif // !FOREACH_H__CONTAINER__COMMONKIT__INCLUDED_
