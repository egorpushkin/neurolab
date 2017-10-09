#ifndef GENERICNETWORK_H__BPFANN__INCLUDED_
#define GENERICNETWORK_H__BPFANN__INCLUDED_

class GenericNetwork
{
public:

	typedef std::vector<IElement*> NetworkContainer;

	GenericNetwork();
		
	// Initialization interface
	void SetElementsFactory(IElementsCollection* piCollection);
	void SetDataFile(IDataFile* piData);
	void SetLogProvider(ILogProvider* piLog);

	// Public interface
	NetworkContainer& GetNetwork();

	bool VerifyNetworkRelevance();
	bool VerifyDataCorrespondence();
	bool VerifyNetworkIntegrity();
	bool CompliteVerification();

	bool IsEmpty();

	void UpdateNetwork(NetworkContainer& sourceNetwork);

private:

    // Private interface
	bool FindElement(IElement* piElement);
	void PutLogMessage(CString& message);

private:

	IElementsCollection* piElementsCollection_;
	IDataFile* piDataFile_;
	ILogProvider* piLogProvider_;

	NetworkContainer network_;

};

#endif // !GENERICNETWORK_H__BPFANN__INCLUDED_
