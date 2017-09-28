#ifndef TRAINER_H__BPFANN__INCLUDED_
#define TRAINER_H__BPFANN__INCLUDED_

class FannTrainer
{
public:

	FannTrainer(
		sBPSettings* pSettings, 		
		IDataFile* piDataFile,
		ILogProvider* piLogProvider,
		GenericNetwork* pNetwork);
	~FannTrainer();

	// Public interface
	bool DoTrainNetwork(); 

private:

	// Private interface
	void DestroyFannTemporaries();
	bool CreateFannNetwork();
	bool CreateFannDataFromDataFile();
	bool TrainFannNetwork();
	bool ExportWeightsToNisdkNetwork();

	// Private fann tools
	unsigned int GetLayersCount(const fann* pAnn);
	unsigned int GetNeuronsCount(const fann_layer* pLayer);
	const fann_layer* GetLayer(const fann* pAnn, unsigned int index);
	const fann_neuron* GetNeuron(const fann_layer* pLayer, unsigned int index);
	float GetNeuronWeight(const fann_neuron* pNeuron, unsigned int index);

private:

	sBPSettings* pSettings_; 
	IDataFile* piDataFile_;
	ILogProvider* piLogProvider_;
	GenericNetwork* pNetwork_;

	fann* fannNetwork_;
	fann_train_data* fannData_;
	
};

#endif // !TRAINER_H__BPFANN__INCLUDED_
