#include "fann.h"

#include "TrainerMain.h"

#include "../NetworkParser/GenericNetwork.h"

#include "FannTrainer.h"

#include "ArgumentsTool.h"

namespace Trainer
{

	GenericNetwork* globalNetwork_ = NULL;

	enum WeightsInitMethods
	{
		WIM_NOINIT				= 0x00,
		WIM_RANDOM				= 0x01,
		WIM_CONSTANT			= 0x02,
		WIM_ADOPTIVE			= 0x03
	};

	FannTrainer::FannTrainer(GenericNetworkRef network)
		: network_(network) 
		, fannNetwork_(NULL)
		, fannData_(NULL)
	{
		globalNetwork_ = GetImpl(network);
	}

	FannTrainer::~FannTrainer()
	{
		DestroyFannTemporaries();
	}

	// Public interface
	result FannTrainer::DoTrainNetwork()
	{
		if ( !network_ )
			return E_FAIL;

		DestroyFannTemporaries();

		// 1. Create fann data
		if ( FAILED(CreateFannDataFromDataFile()) )
			return E_FAIL;

		// 2. Create and tune fann network
		if ( FAILED(CreateFannNetwork()) )
			return E_FAIL;

		// 3. Train network
		if ( FAILED(TrainFannNetwork()) )
			return E_FAIL;

		// 4. Export weights
		if ( FAILED(ExportWeightsToNisdkNetwork()) )
			return E_FAIL;
		
		return S_OK;    
	}

	// Private interface
	void FannTrainer::DestroyFannTemporaries()
	{
		if ( fannNetwork_ )
		{
			fann_destroy(fannNetwork_);
			fannNetwork_ = NULL;
		}

		if ( fannData_ )
		{
			for (unsigned int i = 0; i < fannData_->num_data; ++i)
				delete[] fannData_->input[i];
			delete[] fannData_->input;

			for (unsigned int i = 0; i < fannData_->num_data; ++i)
				delete[] fannData_->output[i];
			delete[] fannData_->output;

			delete fannData_;

			// Cannot use fann_destroy_train(fannData_); because of different method 
			//	applied to allocate memory

			fannData_ = NULL;
		}
	}

	result FannTrainer::CreateFannNetwork()
	{
		if ( !fannData_ )
			return E_FAIL;

		// Create structure
		unsigned int length = (unsigned int)network_->Size();
		GenericNetwork::NetworkDescriptionPtr_ layers = network_->CreateNetworkDescription();		

		fannNetwork_ = fann_create_array(
			1.0f, 
			GetArgument(network_->GetTrainer(), "LearningRate").fltVal_, 
			length, 
			GetImpl(layers));
		
		// Setup parameters
		switch (GetArgument(network_->GetTrainer(), "WeightsInit").uintVal_)
		{
		case WIM_NOINIT: 
			break;
		case WIM_RANDOM: 
			fann_randomize_weights(fannNetwork_, -1.0f, 1.0f);
			break;
		case WIM_CONSTANT: 
			fann_randomize_weights(fannNetwork_, 0.0f, 0.0f);
			break;
		case WIM_ADOPTIVE: 
			fann_init_weights(fannNetwork_, fannData_);
			break;
		}

		fann_set_training_algorithm(fannNetwork_, GetArgument(network_->GetTrainer(), "TrainingMethod").uintVal_);
		fann_set_activation_function_hidden(fannNetwork_, GetArgument(network_->GetTrainer(), "HiddenActivation").uintVal_);
		fann_set_activation_function_output(fannNetwork_, GetArgument(network_->GetTrainer(), "OutputActivation").uintVal_);

		AddTextMessage(network_->GetTrainer(), "N", "FANN network constructed successfully.", "BP Trainer");		

		return S_OK;    
	}

	result FannTrainer::CreateFannDataFromDataFile()
	{
		fannData_ = new fann_train_data;

		fannData_->errno_f = 0;
		fannData_->error_log = NULL;
		fannData_->errstr = NULL;

		fannData_->num_input = network_->GetDataFile()->GetInputSymbolLength();
		fannData_->num_output = network_->GetDataFile()->GetOutputSymbolLength();
		fannData_->num_data = network_->GetDataFile()->GetInputSymbolsCount();

		fannData_->input = new fann_type*[fannData_->num_data];
		for (unsigned int i = 0; i < fannData_->num_data; ++i)
		{
			fannData_->input[i] = new fann_type[fannData_->num_input];
			memcpy(
				fannData_->input[i], 
				network_->GetDataFile()->GetInputSymbol(i)->GetData(), 
				fannData_->num_input * sizeof(float)
			);
		}

		fannData_->output = new fann_type*[fannData_->num_data];
		for (unsigned int i = 0; i < fannData_->num_data; ++i)
		{
			fannData_->output[i] = new fann_type[fannData_->num_output];
			memcpy(
				fannData_->output[i], 
				network_->GetDataFile()->GetOutputSymbol(i)->GetData(), 
				fannData_->num_output * sizeof(float)
			);
		}

		AddTextMessage(network_->GetTrainer(), "N", "Data file converted into FANN internal data format.", "BP Trainer");		

		return true;
	}

	int CallbackReporter(unsigned int epochs, float error)
	{
		char buffer[255];
		sprintf(buffer, "The MSE is %f after %d epoch(s).", error, epochs);
		StringA message(buffer);

		AddTextMessage(globalNetwork_->GetTrainer(), "N", message, "BP Trainer");		

		return 1;
	}

	result FannTrainer::TrainFannNetwork()
	{
		fann_train_on_data_callback(
			fannNetwork_, 
			fannData_, 
			GetArgument(network_->GetTrainer(), "MaxEpochs").uintVal_, 
			GetArgument(network_->GetTrainer(), "EpochsBetweenReport").uintVal_, 
			GetArgument(network_->GetTrainer(), "MaxMSE").fltVal_, 
			CallbackReporter
		);

		return S_OK;    
	}

	result FannTrainer::ExportWeightsToNisdkNetwork()
	{
		unsigned int layers = GetLayersCount(fannNetwork_);

		for ( unsigned int layer = 0 ; layer < layers ; ++layer )
		{
			NiKit::ILayerControlPtr nativeLayer(network_->GetAt(layer + 1), NiKit::IID_ILayerControl);
			const fann_layer* pSourceLayer = GetLayer(fannNetwork_, layer);

			int neurons = nativeLayer->GetDimension();
			int inputs = nativeLayer->GetInputsCount();

			for ( int neuron = 0 ; neuron < neurons ; ++neuron )
			{
				const fann_neuron* pSourceNeuron = GetNeuron(pSourceLayer, neuron);

				for ( int input = 0 ; input < inputs ; ++input )
				{
					float weight = GetNeuronWeight(pSourceNeuron, input);
					nativeLayer->SetWeight(input, neuron, weight);
				}
			}		
		}	

		AddTextMessage(network_->GetTrainer(), "N", "FANN weights were exported to NISDK network.", "BP Trainer");		

		return true;    
	}

	// Private fann tools
	unsigned int FannTrainer::GetLayersCount(const fann* pAnn)
	{			
		if ( !pAnn || 
			!pAnn->first_layer || 
			!pAnn->last_layer || 
			pAnn->first_layer == pAnn->last_layer )
			return 0;

		unsigned int layers = 0;

		fann_layer* last_layer = pAnn->last_layer;
		fann_layer* layer_it = pAnn->first_layer + 1;

		for( ; layer_it != last_layer ; ++layer_it, ++layers );

		return layers;
	}

	const fann_layer* FannTrainer::GetLayer(const fann* pAnn, unsigned int index)
	{
		if ( GetLayersCount(pAnn) <= index )
			return NULL;

		fann_layer* layer_it = pAnn->first_layer + 1;

		for( ; index ; ++layer_it,--index );

		return layer_it;
	}

	unsigned int FannTrainer::GetNeuronsCount(const fann_layer* pLayer)
	{
		if ( !pLayer || 
			!pLayer->first_neuron || 
			!pLayer->last_neuron )
			return 0;

		unsigned int neurons = 0;

		fann_neuron* last_neuron = pLayer->last_neuron;
		fann_neuron* neuron_it = pLayer->first_neuron;

		for( ; neuron_it != last_neuron ; ++neuron_it, ++neurons );

		return --neurons;
	}

	const fann_neuron* FannTrainer::GetNeuron(const fann_layer* pLayer, unsigned int index)
	{
		if ( GetNeuronsCount(pLayer) <= index )
			return NULL;

		fann_neuron* neuron_it = pLayer->first_neuron;

		for( ; index ; ++neuron_it,--index );

		return neuron_it;
	}

	float FannTrainer::GetNeuronWeight(const fann_neuron* pNeuron, unsigned int index)
	{
		if (!pNeuron || 
			!pNeuron->weights || 
			pNeuron->num_connections <= index)
			return 0.0f;

		return pNeuron->weights[index];
	}

} // namespace Trainer








