#ifndef AREASBUILDERTOOLCMD_H__AREASBUILDERTOOL__INCLUDED_
#define AREASBUILDERTOOLCMD_H__AREASBUILDERTOOL__INCLUDED_

class DataGeneratorCmd
{
public: 
	static result Init(int argc, char* const* argv)
	{
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("project", 1, 'p');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("areas", 1, 'a');
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("data", 1, 'd');

		ConsoleHelpersKit::CommandLine::Instance().Parse(argc, argv);

		if ( !ConsoleHelpersKit::CommandLine::Instance().GetOperand('p') || 
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('a') || 
			!ConsoleHelpersKit::CommandLine::Instance().GetOperand('d') )
		{
			ConsoleHelpersKit::Console::EventNotify("Usage: DataGenerator options");
			ConsoleHelpersKit::Console::EventNotify(
				" -p, --project filename       Project file.\n"
				" -a, --areas filename         Areas file.\n"
				" -d, --data filename          Train data.");

			return E_FAIL;
		}

		return S_OK;
	}
};

#endif // !AREASBUILDERTOOLCMD_H__AREASBUILDERTOOL__INCLUDED_
