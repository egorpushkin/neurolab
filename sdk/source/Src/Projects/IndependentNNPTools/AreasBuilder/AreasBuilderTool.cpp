#include "PrecompiledHeader.h"

#include "AreasBuilderCmd.h"

#include "Serialization/XMLProjectParser.h"
#include "Serialization/AreasExporter.h"
#include "Engine/BuilderEngine.h"

using namespace ConsoleHelpersKit;
using namespace Workspace;
using namespace Serialization;
using namespace BuilderEngine;

class AreasBuilderTool 
	: public Application
{
	// Forced declaration of assigment operators
	AreasBuilderTool(const AreasBuilderTool&);
	const AreasBuilderTool& operator =(const AreasBuilderTool&);

public:
	AreasBuilderTool()
		: piAreasProject_(NULL)
	{
		piAreasProject_ = CConstructTool<AreasProject, IAreasProject>::ConstructObject(IID_IAreasProject);		
		if (!piAreasProject_)
			throw ConsoleException("Error initialization AreasProject engine.");
	}
	~AreasBuilderTool()
	{	
        if (piAreasProject_)
			piAreasProject_->Release();
	}

	virtual result Process()
	{
		StringA projectFile(CommandLine::Instance().GetOperand('p'));

		XMLProjectParser parser;
		if (FAILED(parser.LoadProject(projectFile, piAreasProject_)))
		{
			Console::EventNotify(StringA("Error loading areas project file: ") + projectFile + StringA("."));
			return E_FAIL;
		}

		if (FAILED(BuildAeras(piAreasProject_)))
		{
			Console::EventNotify("Failed to build areas of interest.");
			return E_FAIL;
		}		

		AreasExporter exporter;
		if (FAILED(exporter.ExportAreas(piAreasProject_)))
		{
			Console::EventNotify("Failed to export built areas.");
			return E_FAIL;
		}		

		return S_OK;
	}

private:
	IAreasProject*				piAreasProject_;
};

int main(int argc, char* const* argv)
{	
	if (FAILED(AreasBuilderToolCmd::Init(argc, argv)))
		return 0;
                       	
	try
	{
		AreasBuilderTool application;
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


