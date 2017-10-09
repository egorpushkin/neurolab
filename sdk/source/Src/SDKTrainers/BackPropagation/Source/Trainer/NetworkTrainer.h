#ifndef NETWORKTRAINER_H__TRAINTOOL__INCLUDED_
#define NETWORKTRAINER_H__TRAINTOOL__INCLUDED_

namespace Trainer
{

	class NetworkTrainer
	{
	public:
		NetworkTrainer();
		~NetworkTrainer();

		result DoTrain(TrMngKit::ITrainerRef trainer);

	private:
		
		result NetworkTrainer::CaptureNetwork(NiKit::INetworkProcessorRef networkProcessor);
		result NetworkTrainer::CaptureData(DpKit::IDataFileRef trainData);

	private:

		NiKit::INetworkProcessorPtr networkProcessor_;
		DpKit::IDataFilePtr trainData_;

	}; // class NetworkTrainer

} // namespace Trainer

#endif // !NETWORKTRAINER_H__TRAINTOOL__INCLUDED_


