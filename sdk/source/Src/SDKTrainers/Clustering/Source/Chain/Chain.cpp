#include "TrainerMain.h"

#include "ChainCommon.h"
#include "Chain.h"

#include "../Nodes/VerifyData.h"
#include "../Nodes/Clustering.h"

namespace Trainer
{

	ChainOfResp::IChainProcessorPtr CreateChain(TrMngKit::ITrainerPtr trainer)
	{
		ChainOfResp::IChainProcessorPtr chainProcessor = ChainOfResp::CreateProcessor();		

		ChainOfResp::AddNode(chainProcessor, new VerifyData);
		ChainOfResp::AddNode(chainProcessor, new Clustering);

		ChainOfResp::SetInputData(chainProcessor, BaseTrainerHolderPtr(new TrainerHolder(trainer)));

		return chainProcessor;
	}

} // namespace Trainer
