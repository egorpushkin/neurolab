#pragma once

namespace Parser
{

	unsigned int GetLayersCount(const fann* pAnn);
	const fann_layer* GetLayer(const fann* pAnn, unsigned int index);
	
	unsigned int GetNeuronsCount(const fann_layer* pLayer);
	const fann_neuron* GetNeuron(const fann_layer* pLayer, unsigned int index);

	unsigned int GetNeuronInputsCount(const fann_neuron* pNeuron);
	float GetNeuronWeight(const fann_neuron* pNeuron, unsigned int index);		

}
