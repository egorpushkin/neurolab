#ifndef FANNTRAINER_H__BPFANN__INCLUDED_
#define FANNTRAINER_H__BPFANN__INCLUDED_

namespace Trainer
{

	class FannTrainer
	{
	public:

		FannTrainer(GenericNetworkRef network);
		~FannTrainer();

		// Public interface
		result DoTrainNetwork(); 

	private:

		// Private interface
		void DestroyFannTemporaries();
		result CreateFannNetwork();
		result CreateFannDataFromDataFile();
		result TrainFannNetwork();
		result ExportWeightsToNisdkNetwork();

		// Private fann tools
		unsigned int GetLayersCount(const fann* pAnn);
		unsigned int GetNeuronsCount(const fann_layer* pLayer);
		const fann_layer* GetLayer(const fann* pAnn, unsigned int index);
		const fann_neuron* GetNeuron(const fann_layer* pLayer, unsigned int index);
		float GetNeuronWeight(const fann_neuron* pNeuron, unsigned int index);

	private:

		GenericNetworkPtr network_;

		fann* fannNetwork_;
		fann_train_data* fannData_;
		
	};

} // namespace Trainer

#endif // !FANNTRAINER_H__BPFANN__INCLUDED_
