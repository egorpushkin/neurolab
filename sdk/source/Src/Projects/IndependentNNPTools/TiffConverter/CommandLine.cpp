#include "../ConsoleHelpersKit/ConsoleHelpersKit.h"

#include "CommandLine.h"

result CmdProc::Init(int argc, char* const* argv)
{
	ConsoleHelpersKit::CommandLine::Instance().AddOperand("input", 1, 'i');
	ConsoleHelpersKit::CommandLine::Instance().AddOperand("output", 1, 'o');

	ConsoleHelpersKit::CommandLine::Instance().Parse(argc, argv);

	if (!ConsoleHelpersKit::CommandLine::Instance().GetOperand('i') || 
		!ConsoleHelpersKit::CommandLine::Instance().GetOperand('o'))
	{
		ConsoleHelpersKit::Console::EventNotify("Usage: TiffConverter options");
		ConsoleHelpersKit::Console::EventNotify(
			" -i, --input filename         Input file (\"tiff\").\n"
			" -o, --output filename        Input file (\"pgm\").");

		return E_FAIL;
	}

	return S_OK;
}
