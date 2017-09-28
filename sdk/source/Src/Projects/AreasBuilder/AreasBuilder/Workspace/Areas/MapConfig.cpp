#include "stdafx.h"
#include "MapConfig.h"

namespace Workspace
{

MapConfig::MapConfig()
{
}

MapConfig::~MapConfig()
{
}

// Public interface
////////////////////////////////////////////////////////////////////////// 
result MapConfig::AddParameter(const StringA& name, const StringA& value)
{
	parameters_.insert(ParameterPair(name, value));
	return S_OK;	
}

result MapConfig::GetParameter(const StringA& name, StringA& value)
{
	ParametersIterator iter = parameters_.find(name);
	if (parameters_.end() == iter)
		return S_FALSE;

	value = iter->second;

	return S_OK;	
}

uint MapConfig::GetUintParameter(const StringA& name)
{
	StringA value;
	if (GetParameter(name, value) != S_OK)
		return 0;

	return atoi(value.c_str());
}

size_t MapConfig::GetParametersCount()
{
	return parameters_.size();
}

map<StringA, StringA>::const_iterator MapConfig::parametersBegin()
{
	return parameters_.begin();
}

map<StringA, StringA>::const_iterator MapConfig::parametersEnd()
{
	return parameters_.end();
}

}
