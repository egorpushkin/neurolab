#ifndef TRAINTOOLCMD_H__CONSTRUCTTOOL__INCLUDED_
#define TRAINTOOLCMD_H__CONSTRUCTTOOL__INCLUDED_

class TrainToolCmd
{
public: 
	static result Init(int argc, char* const* argv)
	{
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("config", 1, 'c');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("net", 1, 'n');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("data", 1, 'd');

		ConsoleHelpersKit::CommandLine::Instance().Parse(argc, argv);

		if (!ConsoleHelpersKit::CommandLine::Instance().GetOperand('c') || 
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('n') ||
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('d'))
		{
			ConsoleHelpersKit::Console::EventNotify("Usage: TrainTool options");
			ConsoleHelpersKit::Console::EventNotify(
				" -c, --config filename        Configuration file.\n"
				" -n, --net filename           Network project file to be trained (xml format).\n"
				" -d, --data filename          Train data.");

			return E_FAIL;
		}

		return S_OK;
	}
};

#endif // !TRAINTOOLCMD_H__CONSTRUCTTOOL__INCLUDED_
