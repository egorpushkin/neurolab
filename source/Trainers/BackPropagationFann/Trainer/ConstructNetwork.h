#ifndef CONSTRUCTNETWORK_H__BPFANN__INCLUDED_
#define CONSTRUCTNETWORK_H__BPFANN__INCLUDED_

class ConstructNetwork
{
public:

	ConstructNetwork(
		sBPSettings* pSettings, 
		IElementsCollection* piElementsCollection,
		IDataFile* piDataFile,
		ILogProvider* piLogProvider,
		GenericNetwork* pNetwork);

	// Public interface
	bool DoConstructNetwork(); 

private:

	// Private interface
	bool PrivateCustomConstruct(bool skipInitialCheck);
	bool PrivateAutomaticConstruct();

private:

	sBPSettings* pSettings_; 
	IElementsCollection* piElementsCollection_;
	IDataFile* piDataFile_;
	ILogProvider* piLogProvider_;
	GenericNetwork* pNetwork_;

};

#endif // !CONSTRUCTNETWORK_H__BPFANN__INCLUDED_
