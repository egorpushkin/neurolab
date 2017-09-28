#ifndef SMARTPOINTERS_H__MINCOM__COMMONKIT__INCLUDED_
#define SMARTPOINTERS_H__MINCOM__COMMONKIT__INCLUDED_

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4521)
// Multiple constructors required to implement STL compatibility
#endif

template < class T, bool strong = true >
class ComPtr : public Loki::SmartPtr<T, Loki::AdvCOMRefCounted >
{
private:
	typedef Loki::SmartPtr<T, Loki::AdvCOMRefCounted> ComPtrParent;

public:
	ComPtr() 
		: ComPtrParent() 
	{
		ComPtrParent::SetupNew(strong);
	}

	ComPtr(T* p) 
		: ComPtrParent(p) 
	{
		ComPtrParent::SetupNew(strong);
	}

	ComPtr(ComPtr& common)
		: ComPtrParent(common) 
	{
		ComPtrParent::SetStrong(strong);
		ComPtrParent::Clone(GetImpl(common));		
	}

	ComPtr(const ComPtr& common)
		: ComPtrParent(common) 
	{
		ComPtrParent::SetStrong(strong);
		ComPtrParent::Clone(GetImpl(common));		
	}

	template < class U, bool S >
	ComPtr(ComPtr<U, S>& common)
		: ComPtrParent(common) 
	{
		ComPtrParent::SetStrong(strong);
		ComPtrParent::Clone(GetImpl(common));		
	}

	template < class U, bool S >
	ComPtr(const ComPtr<U, S>& common)
		: ComPtrParent(common) 
	{
		ComPtrParent::SetStrong(strong);
		ComPtrParent::Clone(GetImpl(common));		
	}

	template < class U >
	ComPtr(U* ptr, REFIID iid)
		: ComPtrParent() 
	{
		ComPtrParent::SetupNew(strong);

		if (ptr)
			if (FAILED(ptr->QueryInterface(iid, (void**)&GetImplRef(*this))))
				GetImplRef(*this) = NULL;
	}

	template < class U, bool S >
	ComPtr(const ComPtr<U, S>& common, REFIID iid)
		: ComPtrParent() 
	{
		ComPtrParent::SetStrong(strong);

		if (common)
		{
			HRESULT hr = common->QueryInterface(iid, (void**)&GetImplRef(*this));
			if ( FAILED(hr) )
			{
				GetImplRef(*this) = NULL;
			} 
			else
			{
				ComPtrParent::UpdateExistentCounters(common);
				ComPtrParent::IncrementCounters();
			}
		}
	}

	ComPtr& operator=(const ComPtr& rhs)
	{
		ComPtr temp(rhs);
		
		temp.SetStrong(strong);
		temp.Swap(*this);

		return *this;		
	}

	friend inline ComPtr<T, true> GetStrong(const ComPtr& base)
	{
		if (base.CanReturnStrong())
		{
			ComPtr<T, true> resultObject(base);			

			return resultObject;
		}

		return ComPtr<T, true>(NULL);
	}

	friend inline ComPtr<T, false> GetWeak(const ComPtr& base)
	{
		return ComPtr<T, false>(base);
	}

};

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif

////////////////////////////////////////////////////////////////////////////////
// Change log:
// January 8,  2007: Created (based on functionality of Loki)
////////////////////////////////////////////////////////////////////////////////

#endif // !SMARTPOINTERS_H__MINCOM__COMMONKIT__INCLUDED_

// $Log: SmartPointers.h,v $
// Revision 1.3  2007/01/23 21:00:00  scisoftdev
// A lot of bugfixes were applied. STL support 
//
// Revision 1.2  2007/01/13 21:00:00  scisoftdev
// Ugly weak pointers support. 
//
// Revision 1.1  2007/01/08 21:00:00  scisoftdev
// Core functionality implemented.
//
