//	This code is a part of 'Console Helpers Kit' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: ConfigHelper.h
//	Description: ConfigHelper declaration and implementation.  

#ifndef CONFIGHELPER_H__CONSOLEHELPERSKIT__INCLUDED_
#define CONFIGHELPER_H__CONSOLEHELPERSKIT__INCLUDED_

class ConfigHelper
{
public:
	ConfigHelper(StorageProcessorHelper& spHelper)
		: piConfig_(spHelper.GetXMLConfig())
		, parsed_(false)
	{
		if ( FAILED(LoadConfig()) )
			throw ConsoleException("Failed to load configuration file.");
	}

	~ConfigHelper()
	{
		if (piConfig_)
			piConfig_->Release();
	}

	bool IsLoaded()
	{
		return parsed_;
	}

	SpKit::ILayersEnumPtr GetLayersEnum()
	{
		if (!piConfig_)
			throw ConsoleException("ConfigHelper was not properly initialized.");

		return piConfig_->GetLayersEnum();
	}

	SpKit::IArgumentsEnumPtr GetArgumentsEnum()
	{
		if (!piConfig_)
			throw ConsoleException("ConfigHelper was not properly initialized.");

		return piConfig_->GetArgumentsEnum();
	}

private:
	// Private tools
	//////////////////////////////////////////////////////////////////////////
	result LoadConfig()
	{
		StringA configFile(CommandLine::Instance().GetOperand('c'));

		if (FAILED(piConfig_->SerializeConfig(configFile, ModeLoad)))
		{
			Console::EventNotify(StringA("Error loading configuration file: ") + configFile + StringA("."));
			return E_FAIL;
		}

		parsed_ = true;

		return S_OK;
	}

	// Members
	//////////////////////////////////////////////////////////////////////////
	SpKit::IConfig*			piConfig_;

	bool			parsed_;
};

#endif // !CONFIGHELPER_H__CONSOLEHELPERSKIT__INCLUDED_
