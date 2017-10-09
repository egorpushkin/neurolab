#include "stdafx.h"

#include "../Engine/fann.h"

#include "Parser.h"

namespace Parser
{

	unsigned int GetLayersCount(const fann* pAnn)
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

	const fann_layer* GetLayer(const fann* pAnn, unsigned int index)
	{
		if ( GetLayersCount(pAnn) <= index )
			return NULL;

		fann_layer* last_layer = pAnn->last_layer;
		fann_layer* layer_it = pAnn->first_layer + 1;

		for( ; index ; ++layer_it,--index );

		return layer_it;
	}

	unsigned int GetNeuronsCount(const fann_layer* pLayer)
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

	const fann_neuron* GetNeuron(const fann_layer* pLayer, unsigned int index)
	{
		if ( GetNeuronsCount(pLayer) <= index )
			return NULL;

		fann_neuron* last_neuron = pLayer->last_neuron;
		fann_neuron* neuron_it = pLayer->first_neuron;

		for( ; index ; ++neuron_it,--index );

		return neuron_it;
	}

	unsigned int GetNeuronInputsCount(const fann_neuron* pNeuron)
	{
		if (!pNeuron)
			return 0;

        return pNeuron->num_connections;			
	}

	float GetNeuronWeight(const fann_neuron* pNeuron, unsigned int index)
	{
		if (!pNeuron || 
			!pNeuron->weights || 
			pNeuron->num_connections <= index)
			return 0.0f;

		return pNeuron->weights[index];
	}

}


