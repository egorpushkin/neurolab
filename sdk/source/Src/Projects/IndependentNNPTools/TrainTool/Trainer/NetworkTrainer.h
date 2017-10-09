#ifndef NETWORKTRAINER_H__TRAINTOOL__INCLUDED_
#define NETWORKTRAINER_H__TRAINTOOL__INCLUDED_

class NetworkTrainer
{
	// Forced declaration of assignment operators
	NetworkTrainer(const NetworkTrainer&);
	const NetworkTrainer& operator =(const NetworkTrainer&);

public:

	NetworkTrainer(
		ConsoleHelpersKit::StorageProcessorHelper& spHelper,
		ConsoleHelpersKit::TrainersManagerHelper& tmHelper,
		ConsoleHelpersKit::ConfigHelper& cfgHelper);
	~NetworkTrainer();
	
	result CaptureNetwork(NetworkImportingKit::INetworkProcessor* piNetworkProcessor);
	result CaptureData(IDataFile* piTrainData);

	NetworkImportingKit::INetworkProcessor* GetNetwork();

	result TrainNetwork();

private:

	NetworkImportingKit::INetworkProcessor* piNetworkProcessor_;
	IDataFile* piTrainData_;

	ConsoleHelpersKit::StorageProcessorHelper& spHelper_;
	ConsoleHelpersKit::TrainersManagerHelper& tmHelper_;

	ConsoleHelpersKit::ConfigHelper& cfgHelper_;
};

#endif // !NETWORKTRAINER_H__TRAINTOOL__INCLUDED_
