#include "TrainerMain.h"

#include "../Chain/ChainCommon.h"
#include "VerifyData.h"

namespace Trainer
{

	VerifyData::VerifyData() 
		: TrainerChainImpl() 
	{}

	VerifyData::~VerifyData() 
	{}

	// ChainNodeImpl template method
	result VerifyData::DoProcessNode()
	{
		TrainerChainImpl::outputData_ = TrainerChainImpl::inputData_;

		// Acquire trainer object
		TrMngKit::ITrainerPtr trainer = TrainerChainImpl::inputData_->trainer_;

		// Verify properties
		TrMngKit::IPropertiesPtr properties(trainer, TrMngKit::IID_IProperties);
		
		MinCOM::CommonVariant varParam;
		result r = properties->GetArgument(StringA("Width"), varParam);
		if ( FAILED(r) )
		{
			AddTextMessage(trainer, "N", "Image width was not specified.", "Clustering");
			return E_FAIL;
		}
		TrainerChainImpl::inputData_->width_ = varParam.uintVal_;

		r = properties->GetArgument(StringA("Height"), varParam);
		if ( FAILED(r) )
		{
			AddTextMessage(trainer, "N", "Image height was not specified.", "Clustering");
			return E_FAIL;
		}
		TrainerChainImpl::inputData_->height_ = varParam.uintVal_;

		r = properties->GetArgument(StringA("Scale"), varParam);
		if ( SUCCEEDED(r) )
			TrainerChainImpl::inputData_->scale_ = varParam.uintVal_;

		r = properties->GetArgument(StringA("ClustersCount"), varParam);
		if ( SUCCEEDED(r) )
			TrainerChainImpl::inputData_->clustersCount_ = varParam.uintVal_;

		// Acquire data objects
		TrainerChainImpl::inputData_->dataObject1_ = trainer->GetDataObject(TrMngKit::PID_PrimaryParam1);
		if ( !TrainerChainImpl::inputData_->dataObject1_ )
		{
			AddTextMessage(trainer, "N", "Wrong input data (source image) specified.", "Clustering");
			return E_FAIL;
		}

		// Check data objects 
		if ( TrainerChainImpl::inputData_->dataObject1_->GetInputSymbolsCount() == 0 )
		{
			AddTextMessage(trainer, "N", "Source image must contain at least one band.", "Clustering");
			return E_FAIL;
		}

		uint length = 
			TrainerChainImpl::inputData_->width_ * 
			TrainerChainImpl::inputData_->height_;

		if ( TrainerChainImpl::inputData_->dataObject1_->GetInputSymbolLength() != length )
		{
			AddTextMessage(trainer, "N", "Source image length does not correspond to the specified image parameters (width and/or height).", "Clustering");
			return E_FAIL;
		}

		if ( TrainerChainImpl::inputData_->dataObject1_->GetOutputSymbolLength() != length )
		{
			AddTextMessage(trainer, "N", "Output buffer for storing results of clustering has wrong dimension.", "Clustering");
			return E_FAIL;
		}

		return S_OK;
	}

} // namespace Trainer
