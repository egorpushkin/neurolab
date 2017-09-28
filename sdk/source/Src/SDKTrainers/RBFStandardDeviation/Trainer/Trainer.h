#ifndef TRAINER_H__TRAINER__INCLUDED_
#define TRAINER_H__TRAINER__INCLUDED_

namespace Trainer
{

	class Trainer	
		: public TrainersManagerKit::PropertiesImpl
		, public TrainersManagerKit::GeneralProcessorImpl
		, public TrainersManagerKit::TrainerImpl
		, public TrainersManagerKit::ExecutionStateLogImpl
		, public MinCOM::CommonImpl< MinCOM::ICommon > 
	{

		BEGIN_LOCAL_QI_MAP()
			DECLARE_IMPL_CLASS(TrainersManagerKit::PropertiesImpl)
			DECLARE_IMPL_CLASS(TrainersManagerKit::GeneralProcessorImpl)
			DECLARE_IMPL_CLASS(TrainersManagerKit::TrainerImpl)
			DECLARE_IMPL_CLASS(TrainersManagerKit::ExecutionStateLogImpl)
		END_LOCAL_QI_MAP()

	public:
		Trainer();
		virtual ~Trainer();

		// IGeneralProcessor declarations section	
		virtual result Start();

		// ITrainer declarations section		
		virtual result GetTrainerInfo(TrMngKit::PTRAINER_INFO info) const;

		// ICommon declarations section	
		virtual result QueryInterface(REFIID iid, void** ppObject);

	private:

	};

} // namespace Trainer

#endif // !TRAINER_H__TRAINER__INCLUDED_
