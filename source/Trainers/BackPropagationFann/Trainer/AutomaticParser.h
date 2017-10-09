#ifndef AUTOMATICPARSER_H__BPFANN__INCLUDED_
#define AUTOMATICPARSER_H__BPFANN__INCLUDED_

class AutomaticParser
{
public:

	AutomaticParser(
		IElementsCollection* piElementsCollection,
		ILogProvider* piLogProvider,
		GenericNetwork* pNetwork);

	// Public interface
	bool DoConstructNetwork(); 

private:

	// Private interface
	IElement* FindRoot();
	void ContinueChain(IElement* piNode);

private:

	IElementsCollection* piElementsCollection_;
	ILogProvider* piLogProvider_;
	GenericNetwork* pNetwork_;

};

#endif // !AUTOMATICPARSER_H__BPFANN__INCLUDED_
