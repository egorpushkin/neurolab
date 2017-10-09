#ifndef EXTENSION_H__EXTENSION__COMMONKIT__INCLUDED_
#define EXTENSION_H__EXTENSION__COMMONKIT__INCLUDED_

template
<
	class T
>
class Extension
{
public:

	virtual T* InternalGetInstance() const
	{
		return static_cast<T*>(this);
	}

};

template 
<
	class T
>
T* GetInstance()
{
	return static_cast<T*>(
		Loki::SingletonHolder<
			T, 
			Loki::CreateUsingNew, 
			Loki::PhoenixSingleton>::Instance().InternalGetInstance());
}

#endif // !EXTENSION_H__EXTENSION__COMMONKIT__INCLUDED_
