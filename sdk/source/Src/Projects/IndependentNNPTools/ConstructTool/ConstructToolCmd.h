#ifndef CONSTRUCTTOOLCMD_H__CONSTRUCTTOOL__INCLUDED_
#define CONSTRUCTTOOLCMD_H__CONSTRUCTTOOL__INCLUDED_

class ConstructToolCmd
{
public: 
	static result Init(int argc, char* const* argv)
	{
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("config", 1, 'c');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("output", 1, 'o');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("format", 1, 'f');

		ConsoleHelpersKit::CommandLine::Instance().Parse(argc, argv);

		if (!ConsoleHelpersKit::CommandLine::Instance().GetOperand('c') || 
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('o'))
		{
			ConsoleHelpersKit::Console::EventNotify("Usage: ConstructTool options [-f format]");
			ConsoleHelpersKit::Console::EventNotify(
				" -c, --config filename        Configuration file.\n"
				" -o, --output filename        Target network project file.\n"
				" -f, --format format          Project serialization method (\"bin\" or \"xml\").");

			return E_FAIL;
		}

		return S_OK;
	}

	static uint GetOutputFormat()
	{
		uint format = FORMAT_SPXML10;
		if (ConsoleHelpersKit::CommandLine::Instance().GetOperand('f') && 
			StringA(ConsoleHelpersKit::CommandLine::Instance().GetOperand('f')) == StringA("bin"))
			format = FORMAT_DEFBIN10;

		return format;
	}
};

#endif // !CONSTRUCTTOOLCMD_H__CONSTRUCTTOOL__INCLUDED_
