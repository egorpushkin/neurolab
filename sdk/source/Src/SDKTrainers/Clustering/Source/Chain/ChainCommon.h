#ifndef CHAIN_H__TRAINER__INCLUDED_
#define CHAIN_H__TRAINER__INCLUDED_

#include "TrainerHolder.h"

namespace Trainer
{

	typedef ChainOfResp::ChainNodeImpl<
		BaseTrainerHolderPtr, 
		BaseTrainerHolderPtr
	> TrainerChainImpl;

} // namespace Trainer

#endif // !CHAIN_H__TRAINER__INCLUDED_
