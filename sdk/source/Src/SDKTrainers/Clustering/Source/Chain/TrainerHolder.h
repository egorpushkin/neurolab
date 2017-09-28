#ifndef TRAINERHOLDER_H__TRAINER__INCLUDED_
#define TRAINERHOLDER_H__TRAINER__INCLUDED_

namespace Trainer
{
	
	typedef MinCOM::ComPtr< DpKit::IDataFile > IDataFilePtr;

	class BaseTrainerHolder
	{
	public:

		BaseTrainerHolder()
			: trainer_()
			, width_(0)
			, height_(0)
			, clustersCount_(5)
			, scale_(1)
			, dataObject1_()
		{
		}

		TrMngKit::ITrainerPtr trainer_;

		// Source image parameters
		uint width_;
		uint height_;

		// Clustering parameters
		uint clustersCount_;
		uint scale_;

		// Data objects
		IDataFilePtr dataObject1_;

	};

	typedef Loki::SmartPtr< BaseTrainerHolder > BaseTrainerHolderPtr;

	class TrainerHolder : BaseTrainerHolder
	{
	public:

		TrainerHolder(const TrMngKit::ITrainerPtr& trainer)
			: BaseTrainerHolder()
		{
			BaseTrainerHolder::trainer_ = trainer;
		}

	};	

} // namespace Trainer

#endif // !TRAINERHOLDER_H__TRAINER__INCLUDED_
