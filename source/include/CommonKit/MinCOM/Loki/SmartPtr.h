#ifndef SMARTPTR_H__MINCOM__LOKI__INCLUDED_
#define SMARTPTR_H__MINCOM__LOKI__INCLUDED_

// Loki::SmartPtr extension 
//////////////////////////////////////////////////////////////////////////

namespace Loki
{

	template < class P >
	class AdvCOMRefCounted
	{
	public:
		AdvCOMRefCounted() 
			: pStrongCount_(new uintptr_t)
			, pWeakCount_(new uintptr_t)
			, strong_(-1)
		{
			assert(pStrongCount_ != 0);
			assert(pWeakCount_ != 0);
		}

		AdvCOMRefCounted(const AdvCOMRefCounted& rhs) 
			: pStrongCount_(rhs.pStrongCount_)
			, pWeakCount_(rhs.pWeakCount_)
			, strong_(-1)
		{}

		template <typename P1>
		AdvCOMRefCounted(const AdvCOMRefCounted<P1>& rhs) 
			: pStrongCount_(reinterpret_cast<const AdvCOMRefCounted&>(rhs).pStrongCount_)
			, pWeakCount_(reinterpret_cast<const AdvCOMRefCounted&>(rhs).pWeakCount_)
			, strong_(-1)
		{}

		P Clone(const P& val)
		{
			if (strong_ == -1)
				return val;

			IncrementCounters();

			if (strong_ != -1 && strong_ && val != 0)
				val->AddRef();

			return val;
		}

		bool Release(const P& val)
		{
			DecrementCounters();

			if (strong_ != -1 && strong_ && val != 0)
				val->Release();

			if (!*pStrongCount_ && !*pWeakCount_)
			{
				delete pStrongCount_;
				delete pWeakCount_;
				pStrongCount_ = NULL;
				pWeakCount_ = NULL;
			}
			return false;
		}

		void Swap(AdvCOMRefCounted& rhs)
		{ 
			std::swap(pStrongCount_, rhs.pStrongCount_); 
			std::swap(pWeakCount_, rhs.pWeakCount_); 
		}

		enum { destructiveCopy = false };

		// Additional support for weak pointers' tuning
		//////////////////////////////////////////////////////////////////////////
		void SetStrong(bool strong)
		{
			strong_ = strong;
		}

		bool CanReturnStrong() const
		{
			return (*pStrongCount_ > 0);
		}

		void SetupNew(bool strong)
		{
			strong_ = strong;

			*pStrongCount_ = 0;
			*pWeakCount_ = 0;

			IncrementCounters();
		}

		void IncrementCounters()
		{
			if (strong_)
				++*pStrongCount_;
			else 
				++*pWeakCount_;
		}

		void DecrementCounters()
		{
			if (strong_)
				--*pStrongCount_;
			else 
				--*pWeakCount_;
		}

		template <typename P1>
		void UpdateExistentCounters(const AdvCOMRefCounted<P1>& rhs)
		{
			delete pStrongCount_;
			delete pWeakCount_;

			pStrongCount_ = reinterpret_cast<const AdvCOMRefCounted&>(rhs).pStrongCount_;
			pWeakCount_ = reinterpret_cast<const AdvCOMRefCounted&>(rhs).pWeakCount_;
		}

		void UpdateExistentCounters(const AdvCOMRefCounted& rhs)
		{
			delete pStrongCount_;
			delete pWeakCount_;

			pStrongCount_ = rhs.pStrongCount_;
			pWeakCount_ = rhs.pWeakCount_;
		}

		void UpdateExistentCounters(uintptr_t* pStrongCount, uintptr_t* pWeakCount)
		{
			delete pStrongCount_;
			delete pWeakCount_;

			pStrongCount_ = pStrongCount;
			pWeakCount_ = pWeakCount;
		}

	protected:
		// Data
		uintptr_t* pStrongCount_;
		uintptr_t* pWeakCount_;

	private:
		int strong_;
	};

}

#endif // !SMARTPTR_H__MINCOM__LOKI__INCLUDED_
