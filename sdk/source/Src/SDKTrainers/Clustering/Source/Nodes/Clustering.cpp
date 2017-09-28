#include "TrainerMain.h"

#include "../Chain/ChainCommon.h"
#include "Clustering.h"

// LTI includes
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter
#endif

#include <ltiKMeansClustering.h> 

#ifdef _MSC_VER
#pragma warning( pop ) 
#endif

namespace Trainer
{

	Clustering::Clustering() 
		: TrainerChainImpl() 
	{}

	Clustering::~Clustering() 
	{}

	// ChainNodeImpl template method
	result Clustering::DoProcessNode()
	{
		TrainerChainImpl::outputData_ = TrainerChainImpl::inputData_;

		// Acquire trainer object
		TrMngKit::ITrainerPtr trainer = TrainerChainImpl::inputData_->trainer_;

		// Perform clustering
		//////////////////////////////////////////////////////////////////////////

		// Declare and setup clustering functor
		AddTextMessage(trainer, "N", "Preparing functor...", "Clustering");

		lti::kMeansClustering clusteringFunctor;
		
		lti::kMeansClustering::parameters kmParam = clusteringFunctor.getParameters();
		
		kmParam.numberOfClusters = TrainerChainImpl::inputData_->clustersCount_;
		
		clusteringFunctor.setParameters(kmParam);

		// Declare and initialize LTI internal data containers
		AddTextMessage(trainer, "N", "Initializing internal data objects...", "Clustering");

		lti::dmatrix data;
		lti::ivector ids;
		
		int length = TrainerChainImpl::inputData_->dataObject1_->GetInputSymbolLength();
		int bands = TrainerChainImpl::inputData_->dataObject1_->GetInputSymbolsCount();

		data.resize(length, bands, 0, false, false);		
		ids.resize(length, 0, false, false);

		for ( int band = 0 ; band < bands ; ++band ) 
		{
			DpKit::IDataFactory* piBandData = TrainerChainImpl::inputData_->dataObject1_->GetInputSymbol(band);

			for ( int i = 0 ; i < length ; ++i ) 
			{
				data.at(i, band) = piBandData->GetItemData(i);

				ids.at(i) = (int)piBandData->GetItemData(i);
			}
		}

		// Train classifier
		AddTextMessage(trainer, "N", "Training (this may take a long time)...", "Clustering");

        clusteringFunctor.train(data, ids);

		// Save results
		AddTextMessage(trainer, "N", "Postprocessing and serializing results...", "Clustering");

		TrainerChainImpl::inputData_->dataObject1_->AddOutputSymbol(0.0f);
		uint newSymbolIndex = TrainerChainImpl::inputData_->dataObject1_->GetOutputSymbolsCount() - 1;
		DpKit::IDataFactory* piNewSymbol = TrainerChainImpl::inputData_->dataObject1_->GetOutputSymbol(newSymbolIndex);

		for ( int i = 0 ; i < length ; ++i ) 
		{
			piNewSymbol->SetItemData(
				i, (float)(ids.at(i) * TrainerChainImpl::inputData_->scale_));
		}

		return S_OK;
	}

} // namespace Trainer
