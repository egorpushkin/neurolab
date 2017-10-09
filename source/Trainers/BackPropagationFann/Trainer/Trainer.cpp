#include "stdafx.h"

#include "BackProp.h"

#include "Trainer.h"

#include "fann.h"

ILogProvider* piGlobalLogProvider_ = NULL;

FannTrainer::FannTrainer(
	sBPSettings* pSettings, 
	IDataFile* piDataFile,
	ILogProvider* piLogProvider,
	GenericNetwork* pNetwork)
	: pSettings_(pSettings) 
	, piDataFile_(piDataFile)
	, piLogProvider_(piLogProvider)
	, pNetwork_(pNetwork)
	, fannNetwork_(NULL)
	, fannData_(NULL)
{
	piGlobalLogProvider_ = piLogProvider;
}

FannTrainer::~FannTrainer()
{
	DestroyFannTemporaries();
}

// Public interface
bool FannTrainer::DoTrainNetwork()
{
	if ( !pSettings_ || !piDataFile_ || !piLogProvider_ || !pNetwork_ )
		return false;

	DestroyFannTemporaries();

	// 1. Create fann data
	if ( !CreateFannDataFromDataFile() )
		return false;

	// 2. Create and tune fann network
	if ( !CreateFannNetwork() )
		return false;

	// 3. Train network
	if ( !TrainFannNetwork() )
		return false;

	// 4. Export weights
	if ( !ExportWeightsToNisdkNetwork() )
		return false;
	
	return true;    
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
		fann_destroy_train(fannData_);
        fannData_ = NULL;
	}
}

bool FannTrainer::CreateFannNetwork()
{
	if ( !fannData_ )
		return false;

	// Create structure
	size_t length = pNetwork_->GetNetwork().size();
	unsigned int* layers = new unsigned int[length]; 	

	GenericNetwork::NetworkContainer::const_iterator iter = pNetwork_->GetNetwork().begin();
	GenericNetwork::NetworkContainer::const_iterator end = pNetwork_->GetNetwork().end();
	
	for ( int index = 0 ; iter != end ; ++iter, ++index )
	{
		ILayerControl* piLayerControl = NULL;
		(*iter)->QueryInterface(IDD_ILayerControl, (void**)&piLayerControl);

		layers[index] = piLayerControl->GetDimension();
	}
	
	fannNetwork_ = fann_create_array(1.0f, pSettings_->fHiddenTrainSpeed, (unsigned int)length, layers);

    delete[] layers;
	
	// Setup parameters
	switch (pSettings_->iWeightsInitMethod)
	{
	case WIM_NOINIT: 
		break;
	case WIM_RANDOM: 
		fann_randomize_weights(fannNetwork_, pSettings_->fStartRange, pSettings_->fEndRange);
		break;
	case WIM_CONSTANT: 
		fann_randomize_weights(fannNetwork_, pSettings_->fConstant, pSettings_->fConstant);
		break;
	case WIM_ADOPTIVE: 
		fann_init_weights(fannNetwork_, fannData_);
		break;
	}

	fann_set_training_algorithm(fannNetwork_, pSettings_->iTrainingMethod);
	fann_set_activation_function_hidden(fannNetwork_, pSettings_->iHiddenActivation);
	fann_set_activation_function_output(fannNetwork_, pSettings_->iOutputActivation);

	piGlobalLogProvider_->AddLogMessage(
		CString(_T("N")), 
		CString(_T("FANN network constructed successfully.")), 
		CString(_T("Trainer")));		

	return true;    
}

bool FannTrainer::CreateFannDataFromDataFile()
{
	fannData_ = new fann_train_data;

	fannData_->errno_f = 0;
	fannData_->error_log = NULL;
	fannData_->errstr = NULL;

	fannData_->num_input = piDataFile_->GetInputSymbolLength();
	fannData_->num_output = piDataFile_->GetOutputSymbolLength();
	fannData_->num_data = piDataFile_->GetInputSymbolsCount();

	fannData_->input = new fann_type*[fannData_->num_data];
	for (unsigned int i = 0; i < fannData_->num_data; ++i)
	{
		fannData_->input[i] = new fann_type[fannData_->num_input];
		memcpy(fannData_->input[i], piDataFile_->GetInputSymbol(i)->GetData(), fannData_->num_input * sizeof(float));
	}

	fannData_->output = new fann_type*[fannData_->num_data];
	for (unsigned int i = 0; i < fannData_->num_data; ++i)
	{
		fannData_->output[i] = new fann_type[fannData_->num_output];
		memcpy(fannData_->output[i], piDataFile_->GetOutputSymbol(i)->GetData(), fannData_->num_output * sizeof(float));
	}

	piGlobalLogProvider_->AddLogMessage(
		CString(_T("N")), 
		CString(_T("Data file converted into FANN internal data format.")), 
		CString(_T("Trainer")));		

	return true;
}

int CallbackReporter(unsigned int epochs, float error)
{
	CString message;
	message.Format(_T("The MSE is %f after %d epoch(s)."), error, epochs);

	piGlobalLogProvider_->AddLogMessage(CString(_T("N")), message, CString(_T("CallbackReporter")));		

	return 1;
}

bool FannTrainer::TrainFannNetwork()
{
	fann_train_on_data_callback(
		fannNetwork_, 
		fannData_, 
		pSettings_->iMaxLoopsCount, 
		1, 
		pSettings_->fMaxError, 
		CallbackReporter
	);

	return true;    
}

bool FannTrainer::ExportWeightsToNisdkNetwork()
{
	unsigned int layers = GetLayersCount(fannNetwork_);

	for ( unsigned int layer = 0 ; layer < layers ; ++layer )
	{
		ILayerControl* piNativeLayer = NULL;
		(pNetwork_->GetNetwork().at(layer + 1))->QueryInterface(IDD_ILayerControl, (void**)&piNativeLayer);

		const fann_layer* pSourceLayer = GetLayer(fannNetwork_, layer);

		int neurons = piNativeLayer->GetDimension();
		int inputs = piNativeLayer->GetInputsCount();

		for ( int neuron = 0 ; neuron < neurons ; ++neuron )
		{
			const fann_neuron* pSourceNeuron = GetNeuron(pSourceLayer, neuron);

			for ( int input = 0 ; input < inputs ; ++input )
			{
				float weight = GetNeuronWeight(pSourceNeuron, input);
                piNativeLayer->SetWeight(input, neuron, weight);
			}
		}		
	}	

	piGlobalLogProvider_->AddLogMessage(
		CString(_T("N")), 
		CString(_T("FANN weights were exported to NISDK network.")), 
		CString(_T("Trainer")));	

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

	fann_layer* last_layer = pAnn->last_layer;
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

	fann_neuron* last_neuron = pLayer->last_neuron;
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








