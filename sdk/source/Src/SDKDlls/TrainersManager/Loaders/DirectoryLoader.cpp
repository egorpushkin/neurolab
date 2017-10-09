#include "../TrainersManager.h"

#include "DirectoryLoader.h"

#include "LoadHelper.h"

using namespace ComponentsKit;
using namespace TrainersManagerKit;

DirectoryLoader::DirectoryLoader()
	: arguments_()
	, fileInfo_()
	, searchDone_(-1)
	, folderName_()
{
}

DirectoryLoader::~DirectoryLoader()
{
}

// ITrainersLoader implementations section	
result DirectoryLoader::SetArgumentName(const StringA& argName, const StringA& value)
{
	std::pair<ArgumentsIterator, bool> iter = arguments_.insert(ArgumentsPair(argName, value));
    
	return (iter.second ? S_OK : S_FALSE);
}

IComponentLoader* DirectoryLoader::LoadFirstTrainer()
{
	StringA trainersFolder("");
	ArgumentsIterator iter = arguments_.find(LOADER_PARAM_DIR_NAME);
	if (iter != arguments_.end())
		trainersFolder = (*iter).second;

	folderName_ =
		StringA("./") + 
		trainersFolder;

	StringA folderPattern =
		folderName_ + 
		StringA("/*") + 
		SO_LIB_EXT;

	searchDone_ = _findfirst(folderPattern.c_str(), &fileInfo_);	
	if (searchDone_ == -1)
		return NULL;

	StringA libraryName =
		folderName_ + 
		StringA("/") + 
		StringA(fileInfo_.name);

	// Try load library 
	IComponentLoader* piLoader = NULL;

	result res = LoadHelper::TryLoadLibrary(libraryName, &piLoader);
	if (FAILED(res))
		return LoadNextTrainer();

	return piLoader;
}

IComponentLoader* DirectoryLoader::LoadNextTrainer()
{
	int done = _findnext(searchDone_, &fileInfo_);
	if (done == -1)
		return NULL;

	StringA libraryName =
		folderName_ + 
		StringA("/") + 
		StringA(fileInfo_.name);

	// Try load library 
	IComponentLoader* piLoader = NULL;

	result res = LoadHelper::TryLoadLibrary(libraryName, &piLoader);
	if (FAILED(res))
		return LoadNextTrainer();	
    
	return piLoader;
}

// ICommon implementations section	
result DirectoryLoader::QueryInterface(REFIID iid, void** ppObject)
{
	if (iid == MinCOM::IID_ICommon)
		*ppObject = MinCOM::CommonImpl< ITrainersLoader >::GetCommon();

	else if (iid == IID_ITrainersLoader)
		*ppObject = static_cast< ITrainersLoader* >(this);

	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	MinCOM::CommonImpl< ITrainersLoader >::GetCommon()->AddRef();
	return S_OK;	
}
