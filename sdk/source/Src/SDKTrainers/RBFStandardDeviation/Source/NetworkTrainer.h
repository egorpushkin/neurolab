#ifndef NETWORKTRAINER_H__TRAINTOOL__INCLUDED_
#define NETWORKTRAINER_H__TRAINTOOL__INCLUDED_

namespace Trainer
{

	class NetworkTrainer
	{
	public:
		NetworkTrainer()
			: piNetworkProcessor_(NULL)
			, piTrainData_(NULL)
			, inputLength_(0)
			, classesCount_(0)
			, samplesPerClass_(0)
			, weight_(2.0f)
		{
		}

		~NetworkTrainer()
		{
			if (piNetworkProcessor_)
				piNetworkProcessor_->Release();
			if (piTrainData_)
				piTrainData_->Release();
		}

		result DoTrain(TrMngKit::ITrainer* piTrainer)
		{
			// Properties access
			TrMngKit::IProperties* piProperties = NULL;
			piTrainer->QueryInterface(TrMngKit::IID_IProperties, (void**)&piProperties);
			
			MinCOM::CommonVariant varParam;
			result r = piProperties->GetArgument(StringA("InputVectorLength"), varParam);
			if ( FAILED(r) || varParam.vt_ != MinCOM::CE_UINT )
			{
				piProperties->Release();
				return E_FAIL;
			}
			inputLength_ = varParam.uintVal_;

			r = piProperties->GetArgument(StringA("ClassesCount"), varParam);
			if ( FAILED(r) || varParam.vt_ != MinCOM::CE_UINT )
			{
				piProperties->Release();
				return E_FAIL;
			}
			classesCount_ = varParam.uintVal_;

			r = piProperties->GetArgument(StringA("SamplesPerClass"), varParam);
			if ( FAILED(r) || varParam.vt_ != MinCOM::CE_UINT )
			{
				piProperties->Release();
				return E_FAIL;
			}
			samplesPerClass_ = varParam.uintVal_;

			r = piProperties->GetArgument(StringA("WeightValue"), varParam);
			if ( FAILED(r) || varParam.vt_ != MinCOM::CE_R4 )
			{
				piProperties->Release();
				return E_FAIL;
			}
			weight_ = varParam.fltVal_;

			piProperties->Release();

			// Capture data objects
			if ( FAILED(CaptureNetwork(piTrainer->GetNetwork(TrMngKit::PID_PrimaryParam1))) )
				return E_FAIL;

			if ( FAILED(CaptureData(piTrainer->GetDataObject(TrMngKit::PID_PrimaryParam1))) )
				return E_FAIL;

			return TrainNetwork(piTrainer);
		}
		
		result CaptureNetwork(NetworkImportingKit::INetworkProcessor* piNetworkProcessor)
		{
			piNetworkProcessor_ = piNetworkProcessor;
			return (piNetworkProcessor_ ? S_OK : E_FAIL);
		}

		result CaptureData(IDataFile* piTrainData)
		{
			piTrainData_ = piTrainData;
			return (piTrainData_ ? S_OK : E_FAIL);
		}

		result TrainNetwork(TrMngKit::ITrainer* piTrainer)
		{
			// Step 1. Receiving required layers
			NetworkImportingKit::ILayerControl* piRBFLayer = GetLayerByName(StringA("RBFLayer"));
			NetworkImportingKit::ILayerControl* piNeuronsLayer = GetLayerByName(StringA("NeuronsLayer"));

			// Step 2. Check network settings
			if ( !piRBFLayer || !piNeuronsLayer )
			{
				AddTextMessage(piTrainer, "E", "Wrong network structure.", "RBF Trainer");

				if ( piRBFLayer )
					piRBFLayer->Release();
				if ( piNeuronsLayer )
					piNeuronsLayer->Release();

				return E_FAIL;
			}

			if ( piRBFLayer->GetInputsCount() != inputLength_ ||
				piRBFLayer->GetDimension() != (classesCount_ * samplesPerClass_) || 
				piNeuronsLayer->GetInputsCount() != (classesCount_ * samplesPerClass_) ||
				piNeuronsLayer->GetDimension() != classesCount_ )
			{
				AddTextMessage(piTrainer, "E", "Wrong network configuration.", "RBF Trainer");

				piRBFLayer->Release();
				piNeuronsLayer->Release();

				return E_FAIL;
			}

			// Step 3. Train layers
			TrainRBFLayer(piRBFLayer);
			TrainNeuronsLayer(piNeuronsLayer);

			// Release local objects
			piRBFLayer->Release();
			piNeuronsLayer->Release();

			return S_OK;
		}

		NetworkImportingKit::ILayerControl* GetLayerByName(const StringA& name)
		{
			NetworkImportingKit::IElementsCollection* piElements = 
				QueryTool<NetworkImportingKit::INetworkProcessor, NetworkImportingKit::IElementsCollection>::
					QueryInterface(piNetworkProcessor_, NetworkImportingKit::IID_IElementsCollection);

			NetworkImportingKit::ILayerControl* piFoundLayer = NULL;

			NetworkImportingKit::IElementsEnumerator* piEnum = piElements->GetElementsEnumerator();
			for (bool hasElements = piEnum->SelectFirst();hasElements;hasElements = piEnum->SelectNext())
			{
				NetworkImportingKit::IElement* piElement = piEnum->GetSelected();

				piFoundLayer = QueryTool<NetworkImportingKit::IElement, NetworkImportingKit::ILayerControl>::
					QueryInterface(piElement, NetworkImportingKit::IID_ILayerControl);
				if (!piFoundLayer)
					continue;

				if (piElement->GetSysName() == name)
					break;

				piFoundLayer->Release();
				piFoundLayer = NULL;
			}		
			piEnum->Release();

			piElements->Release();
				
			return piFoundLayer;
		}

		result TrainRBFLayer(NetworkImportingKit::ILayerControl* piRBFLayer)
		{
			for (uint i = 0;i < piTrainData_->GetInputSymbolsCount();i++)
				for (uint j = 0;j < piTrainData_->GetInputSymbolLength();j++)
					piRBFLayer->SetWeight(j, i, 
						piTrainData_->GetInputSymbol(i)->GetItemData(j));
			
			for (uint i = 0;i < piRBFLayer->GetDimension();i++)
			{
				float deltaValue = 1000*1000;
				for (uint j = 0;j < piTrainData_->GetInputSymbolsCount();j++)
				{
					if (i != j && !IsBelongToTheSameClass(i, j))
					{
						float distance = GetHalfDistance(i, j);
						if (distance < deltaValue)
							deltaValue = distance;
					}
				}

				piRBFLayer->SetDelta(i, deltaValue);
			}

			return S_OK;
		}

		result TrainNeuronsLayer(NetworkImportingKit::ILayerControl* piNeuronsLayer)
		{
			for (uint i = 0;i < piNeuronsLayer->GetDimension();i++)
				for (uint j = 0;j < piNeuronsLayer->GetInputsCount();j++)
				{
					float multiplier = 1.0f;

					if ((j < i * samplesPerClass_) ||
						(j >= (i + 1) * samplesPerClass_)) 
							multiplier = -1;          

					piNeuronsLayer->SetWeight(j, i, multiplier * weight_);
				}

			return S_OK;
		}

		bool IsBelongToTheSameClass(uint index1, uint index2)
		{
			for (uint i = 0; i < piTrainData_->GetOutputSymbolLength();i++)
			{
				float val1 = piTrainData_->GetOutputSymbol(index1)->GetItemData(i);
				float val2 = piTrainData_->GetOutputSymbol(index2)->GetItemData(i);

				if (val1 != val2)
					return false;
			}

			return true; 
		}

		float GetHalfDistance(uint index1, uint index2)
		{
			float distance = 0;
			for (uint i = 0; i < piTrainData_->GetInputSymbolLength();i++)
			{
				float val1 = piTrainData_->GetInputSymbol(index1)->GetItemData(i);
				float val2 = piTrainData_->GetInputSymbol(index2)->GetItemData(i);

				distance += ((val1 - val2) * (val1 - val2));
			}

			distance = sqrt(distance);

			return distance / 2; 
		}

	private:
		NetworkImportingKit::INetworkProcessor*		piNetworkProcessor_;
		IDataFile*									piTrainData_;

		uint inputLength_;
		uint classesCount_;
		uint samplesPerClass_;
		float weight_;
	};

} // namespace Trainer

#endif // !NETWORKTRAINER_H__TRAINTOOL__INCLUDED_


