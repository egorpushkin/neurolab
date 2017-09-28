#ifndef ENUMERATORS_H__TRAINERSMANAGER__INCLUDED_
#define ENUMERATORS_H__TRAINERSMANAGER__INCLUDED_

namespace TrainerLocators
{

	class BasicEnumerator
	{
	public:

		TrMngKit::ITrainer* GetFoundTrainer()
		{
			if (piFoundTrainer_)
				piFoundTrainer_->AddRef();
			return piFoundTrainer_;
		}

	protected:
		BasicEnumerator()
			: piFoundTrainer_(NULL)
		{
		}
		
		TrMngKit::ITrainer* piFoundTrainer_;
	};

	class LocateIndex : public BasicEnumerator
	{
	public:
		LocateIndex(uint index)
			: requierdIndex_(index)
			, currentIndex_(0)
		{
		}
		
		void operator ()(TrMngKit::ITrainer* piTrainer)
		{
			if (currentIndex_ == requierdIndex_)
				BasicEnumerator::piFoundTrainer_ = piTrainer;

			++currentIndex_;
		}

	private:
		uint requierdIndex_;
		uint currentIndex_;
	};

	class LocateName : public BasicEnumerator
	{
		const LocateName& operator =(const LocateName&);

	public:
		LocateName(const StringA& name, const TrMngKit::PVERSION minVersion = NULL)
			: name_(name)
			, minVersion_(minVersion)
		{
		}

		void operator ()(TrMngKit::ITrainer* piTrainer)
		{	
			TrMngKit::TRAINER_INFO info;
			piTrainer->GetTrainerInfo(&info);

			if ((name_ == info.name_) && 
				((minVersion_ && ( (info.version_) >= (*minVersion_) )) || (!minVersion_)))
					BasicEnumerator::piFoundTrainer_ = piTrainer;
		}

	private:
		const StringA& name_;
		const TrMngKit::PVERSION minVersion_;	
	};

	class LocateClsid : public BasicEnumerator
	{
		const LocateClsid& operator =(const LocateClsid&);

	public:
		LocateClsid(REFCLSID clsid, const TrMngKit::PVERSION minVersion = NULL)
			: clsid_(clsid)
			, minVersion_(minVersion)
		{
		}

		void operator ()(TrMngKit::ITrainer* piTrainer)
		{	
			TrMngKit::TRAINER_INFO info;
			piTrainer->GetTrainerInfo(&info);

			if ((clsid_ == info.clsid_) && 
				((minVersion_ && ( (info.version_) >= (*minVersion_) )) || (!minVersion_)))
				BasicEnumerator::piFoundTrainer_ = piTrainer;
		}

	private:
		REFCLSID clsid_;
		const TrMngKit::PVERSION minVersion_;	
	};

}

#endif // !ENUMERATORS_H__TRAINERSMANAGER__INCLUDED_
