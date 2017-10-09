#ifndef PROJECTCONVERTERCMD_H__CONSTRUCTTOOL__INCLUDED_
#define PROJECTCONVERTERCMD_H__CONSTRUCTTOOL__INCLUDED_

class ProjectConverterCmd
{
public: 
	static result Init(int argc, char* const* argv)
	{
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("src", 1, 's');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("dst", 1, 'd');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("conv", 1, 'c');

		ConsoleHelpersKit::CommandLine::Instance().Parse(argc, argv);

		if (!ConsoleHelpersKit::CommandLine::Instance().GetOperand('s') || 
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('d') || 
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('c'))
		{
			ConsoleHelpersKit::Console::EventNotify("Usage: ProjectConverter options");
			ConsoleHelpersKit::Console::EventNotify(
				" -s, --src filename           Network project source file.\n"
				" -d, --dst filename           Network project destination file.\n"
				" -c, --conv method            Converting method (\"bin2xml\" or \"xml2bin\").");
			
			return E_FAIL;
		}

		return S_OK;
	}

	static uint GetConversionMethod()
	{
		uint convertionMethod = CONV_UNEXPECTED;  
		if (!strcmp(ConsoleHelpersKit::CommandLine::Instance().GetOperand('c'), "xml2bin"))
			convertionMethod = CONV_SPXML10_TO_DEFBIN10;  
		else if (!strcmp(ConsoleHelpersKit::CommandLine::Instance().GetOperand('c'), "bin2xml"))
			convertionMethod = CONV_DEFBIN10_TO_SPXML10; 

		return convertionMethod;
	}
};

#endif // !PROJECTCONVERTERCMD_H__CONSTRUCTTOOL__INCLUDED_
