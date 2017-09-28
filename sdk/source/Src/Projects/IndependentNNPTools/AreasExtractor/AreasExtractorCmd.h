#ifndef AREASEXTRACTORCMD_H__AREASEXTRACTOR__INCLUDED_
#define AREASEXTRACTORCMD_H__AREASEXTRACTOR__INCLUDED_

class AreasExtractorCmd
{
public: 
	static result Init(int argc, char* const* argv)
	{
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("project", 1, 'p');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("map", 1, 'm');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("areas", 1, 'a');		

		ConsoleHelpersKit::CommandLine::Instance().Parse(argc, argv);

		if ( !ConsoleHelpersKit::CommandLine::Instance().GetOperand('p') || 
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('m') || 
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('a') )
		{
			ConsoleHelpersKit::Console::EventNotify("Usage: AreasExtractor options");
			ConsoleHelpersKit::Console::EventNotify(
				" -p, --project filename       Project file\n"
				" -m, --map filename           Map file\n"
				" -a, --areas filename         Areas file.\n");

			return E_FAIL;
		}

		return S_OK;
	}
};

#endif // !AREASEXTRACTORCMD_H__AREASEXTRACTOR__INCLUDED_
