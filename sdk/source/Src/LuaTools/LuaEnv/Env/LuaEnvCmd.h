#ifndef LUAENVCMD_H__LUAENV__INCLUDED_
#define LUAENVCMD_H__LUAENV__INCLUDED_

class LuaEnvCmd
{
public: 
	static result Init(int argc, char* const* argv)
	{
		ConsoleHelpersKit::CommandLine::Instance().AddOperand("script", 1, 's');

		ConsoleHelpersKit::CommandLine::Instance().Parse(argc, argv);

		if (!ConsoleHelpersKit::CommandLine::Instance().GetOperand('s'))
			return E_FAIL;

		return S_OK;
	}

	static void TypeUsage()
	{
		ConsoleHelpersKit::Console::EventNotify("Usage: LuaEnv options");
		ConsoleHelpersKit::Console::EventNotify(
			" -s, --script filename        Script to be executed.");
	}
};

#endif // !LUAENVCMD_H__LUAENV__INCLUDED_
