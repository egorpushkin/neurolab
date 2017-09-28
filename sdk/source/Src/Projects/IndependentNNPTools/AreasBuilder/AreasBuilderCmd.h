#ifndef AREASBUILDERTOOLCMD_H__AREASBUILDERTOOL__INCLUDED_
#define AREASBUILDERTOOLCMD_H__AREASBUILDERTOOL__INCLUDED_

class AreasBuilderToolCmd
{
public: 
	static result Init(int argc, char* const* argv)
	{
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("project", 1, 'p');

		ConsoleHelpersKit::CommandLine::Instance().Parse(argc, argv);

		if (!ConsoleHelpersKit::CommandLine::Instance().GetOperand('p'))
		{
			ConsoleHelpersKit::Console::EventNotify("Usage: AreasBuilderTool options");
			ConsoleHelpersKit::Console::EventNotify(
				" -p, --project filename       Project file.");

			return E_FAIL;
		}

		return S_OK;
	}
};

#endif // !AREASBUILDERTOOLCMD_H__AREASBUILDERTOOL__INCLUDED_
