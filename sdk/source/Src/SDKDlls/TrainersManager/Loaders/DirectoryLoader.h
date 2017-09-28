#ifndef DIRECTORYLOADER_H__TRAINERSMANAGER__INCLUDED_
#define DIRECTORYLOADER_H__TRAINERSMANAGER__INCLUDED_

class DirectoryLoader 
	: public MinCOM::CommonImpl< TrainersManagerKit::ITrainersLoader >
{
public:
	DirectoryLoader();
	virtual ~DirectoryLoader();

	// ITrainersLoader declarations section	
	virtual result SetArgumentName(const StringA& argName, const StringA& value);

	virtual ComponentsKit::IComponentLoader* LoadFirstTrainer();
	virtual ComponentsKit::IComponentLoader* LoadNextTrainer();

	// ICommon declarations section	
	virtual result						QueryInterface(REFIID iid, void** ppObject);

private:

	typedef std::pair<const StringA, const StringA> ArgumentsPair;
	typedef std::map<ArgumentsPair::first_type, ArgumentsPair::second_type>::iterator ArgumentsIterator;

	std::map<ArgumentsPair::first_type, ArgumentsPair::second_type> arguments_;

	_finddata_t fileInfo_;
	intptr_t searchDone_;
	StringA folderName_;

};

#endif // !DIRECTORYLOADER_H__TRAINERSMANAGER__INCLUDED_
