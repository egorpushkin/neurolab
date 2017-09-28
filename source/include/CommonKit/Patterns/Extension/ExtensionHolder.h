#ifndef EXTENSIONHOLDER_H__EXTENSION__COMMONKIT__INCLUDED_
#define EXTENSIONHOLDER_H__EXTENSION__COMMONKIT__INCLUDED_

template
<
	class T
>
class ExtensionHolder
{
public:

	ExtensionHolder()
		: extension_(NULL)
	{
	}

	ExtensionHolder(T* extension)
		: extension_(extension)
	{
	}

	void SetExtension(T* extension)
	{
		extension_ = extension;
	}

	T* GetExtension() const 
	{
		return extension_;
	}

	T* operator->() const
	{
		assert(extension_ != NULL);
		return extension_;
	}

private:
	T* extension_;
};

#endif // !EXTENSIONHOLDER_H__EXTENSION__COMMONKIT__INCLUDED_
