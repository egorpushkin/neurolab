//	This code is a part of 'Console Helpers Kit' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: CommandLine.h
//	Description: Command line argumenta processing helper object implementation.  

#ifndef COMMANDLINE_H__CONSOLEHELPERSKIT__INCLUDED_
#define COMMANDLINE_H__CONSOLEHELPERSKIT__INCLUDED_

class CommandLineTool
{
public:
	CommandLineTool()
		: parsed_(false)
		, operands_()
		, shortOptions_("")
		, longOptions_()
	{
	}

	void AddOperand(char* longName, int hasArgument, char shortName)
	{		
		shortOptions_.push_back(shortName);
		if (hasArgument)
			shortOptions_.push_back(':');

		option temporaryOption;
		temporaryOption.name = longName;
		temporaryOption.has_arg = hasArgument;
		temporaryOption.flag = NULL;
		temporaryOption.val = shortName;
        
		longOptions_.push_back(temporaryOption);
	}

	void Parse(int argc, char* const* argv)
	{
		if (parsed_)
			return;

		AddOperand(NULL, 0, 0);

		DECLARE_GETOTP_TOOL

		char nextOption = '\x0';
		do 
		{
			nextOption = (char)GETOPT_CALL(argc, argv, shortOptions_.c_str(), &(*longOptions_.begin()), NULL);
			switch (nextOption)
			{
			case -1: 
				break;
			default: 
				operands_.insert(OperandPair(nextOption, GETOPT_ARG));
				break;
			}
		} while (nextOption != -1);			

		shortOptions_.clear();
		longOptions_.clear();

		parsed_ = true;
	}

	const char* GetOperand(char opName)
	{
		OperandsIterator iter = operands_.find(opName);
		if (iter == operands_.end())
			return NULL;

		if (!iter->second)
			return "";
            
		return iter->second;
	}

private:
	bool										parsed_;

	StringA										shortOptions_;
	vector<option>								longOptions_;

	map<char, const char*>						operands_;
	typedef pair<char, const char*>				OperandPair;
	typedef map<char, const char*>::iterator	OperandsIterator;
};

typedef Loki::SingletonHolder<CommandLineTool, Loki::CreateUsingNew, Loki::DeletableSingleton> CommandLine;
typedef Loki::DeletableSingleton< CommandLineTool > CommandLineDeleter;

class CommandLineException : public ConsoleException 
{};

template
<
	class T
> 
class CommandLineHolder
{
public:
	CommandLineHolder(int argc, char* const* argv)
	{
		if ( FAILED(T::Init(argc, argv)) )
            throw CommandLineException();
	}
	~CommandLineHolder()
	{
		CommandLineDeleter::GracefulDelete();
	}

};

#endif // !COMMANDLINE_H__CONSOLEHELPERSKIT__INCLUDED_
