#include "PrecompiledHeader.h"

#include "DataGeneratorCmd.h"

#include "Serialization/XMLProjectParser.h"
#include "Serialization/TrainDataSerializer.h"

#include "AreasTool/AreasTool.h"
#include "AreasTool/Serializer.h"

#include "Generator/Generator.h"

using namespace ConsoleHelpersKit;
using namespace Workspace;


class DataGenerator
	: public Application
{

	// Forced declaration of assignment operators
	DataGenerator(const DataGenerator&);
	const DataGenerator& operator =(const DataGenerator&);

public:

	DataGenerator()
		: piAreasProject_(CConstructTool<AreasProject, IAreasProject>::ConstructObject(IID_IAreasProject))
		, pAreasTool_(new Areas::AreasTool)
		, piDataFile_(CConstructTool<CDataFile, IDataFile>::ConstructObject(IID_IDataFile))
	{
		if ( !piAreasProject_ )
			throw ConsoleException("Error initialization AreasProject engine.");

		if ( !pAreasTool_ )
			throw ConsoleException("Error creating AreasTool.");

		if ( !piDataFile_ )
			throw ConsoleException("Failed to create DataFile.");
	}
	~DataGenerator()
	{	
        if ( piAreasProject_ )
			piAreasProject_->Release();

		if ( piDataFile_ )
			piDataFile_->Release();

		delete pAreasTool_;
	}

	virtual result Process()
	{
		StringA projectFile(CommandLine::Instance().GetOperand('p'));
		StringA areasFile(CommandLine::Instance().GetOperand('a'));
		StringA trainFile(CommandLine::Instance().GetOperand('d'));

		Console::EventNotify("Loading project...");

		Serialization::XMLProjectParser parser;
		if ( FAILED(parser.LoadProject(projectFile, piAreasProject_)) )
		{
			Console::EventNotify(StringA("Error loading areas project file: ") + projectFile + StringA("."));
			return E_FAIL;
		}

		Console::EventNotify("Loading areas...");

		Areas::Serializer areasSerializer;
		if ( FAILED(areasSerializer.LoadAreas(areasFile, pAreasTool_)) )
		{
			Console::EventNotify("Failed to load areas of interest.");
			return E_FAIL;
		}

		Console::EventNotify("Grabbing fragments for training...");

		Generator::TrainDataGenerator generator;
		if ( FAILED(generator.Generate(piAreasProject_, pAreasTool_, piDataFile_)) )
		{
			Console::EventNotify("Failed to generate data file.");
			return E_FAIL;
		}

		Console::EventNotify("Serializing output...");

		if ( FAILED(Serialization::TrainDataSerializer::StoreData(trainFile, piDataFile_)) )
		{
			Console::EventNotify("Failed to generate data file.");
			return E_FAIL;
		}

		return S_OK;
	}

private:

	IAreasProject*				piAreasProject_;
	Areas::AreasTool*			pAreasTool_;
	IDataFile*					piDataFile_;

};

int main(int argc, char* const* argv)
{	
	if (FAILED(DataGeneratorCmd::Init(argc, argv)))
		return 0;
                       	
	try
	{
		DataGenerator application;
		application.Process();
	} 
	catch (exception& ex)
	{
		Console::EventNotify("Abnormal program termination caused by the following reason:");
		Console::EventNotify(ex.what());
	}
	catch (...)
	{
		Console::EventNotify("Abnormal program termination caused by unknown reason.");
	}

#ifdef _MSC_VER 
	_CrtDumpMemoryLeaks(); 
#endif // _MSC_VER

	return 0;
}


