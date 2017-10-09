#ifndef PROCESSTOOLCMD_H__CONSTRUCTTOOL__INCLUDED_
#define PROCESSTOOLCMD_H__CONSTRUCTTOOL__INCLUDED_

class ProcessToolCmd
{
public: 
	static result Init(int argc, char* const* argv)
	{
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("config", 1, 'c');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("net", 1, 'n');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("input", 1, 'i');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("output", 1, 'o');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("format", 1, 'f');

		ConsoleHelpersKit::CommandLine::Instance().Parse(argc, argv);

		if (!ConsoleHelpersKit::CommandLine::Instance().GetOperand('c') || 
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('n') ||
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('i') ||
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('o'))
		{
			ConsoleHelpersKit::Console::EventNotify("Usage: ProcessTool options [-f format]");
			ConsoleHelpersKit::Console::EventNotify(
				" -c, --config filename        Configuration file.\n"
				" -n, --net filename           Network project file to be trained (xml format).\n"
				" -i, --input filename         Input data.\n"
				" -o, --output filename        Output data\n"
				" -f, --format format          Data format (\"txt\" or \"tiff\").");

			return E_FAIL;
		}

		return S_OK;
	}

	static uint GetDataFormat()
	{
		uint format = DATA_FORMAT_PLAIN_TEXT;
		if (ConsoleHelpersKit::CommandLine::Instance().GetOperand('f') && 
			StringA(ConsoleHelpersKit::CommandLine::Instance().GetOperand('f')) == StringA("tiff"))
			format = DATA_FORMAT_TIFF;

		return format;
	}
};

#endif // !PROCESSTOOLCMD_H__CONSTRUCTTOOL__INCLUDED_
