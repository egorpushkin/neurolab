#ifndef MAPCONFIG_H__WORKSPACE__INCLUDED_
#define MAPCONFIG_H__WORKSPACE__INCLUDED_

namespace Workspace
{

class MapConfig
{
public:
	MapConfig();
	virtual ~MapConfig();

	// Public interface
	////////////////////////////////////////////////////////////////////////// 
	virtual result			AddParameter(const StringA& name, const StringA& value);
	virtual result			GetParameter(const StringA& name, StringA& value);
	virtual uint			GetUintParameter(const StringA& name);
	virtual float			GetFloatParameter(const StringA& name);

	virtual size_t			GetParametersCount();

    virtual map<StringA, StringA>::const_iterator parametersBegin();
	virtual map<StringA, StringA>::const_iterator parametersEnd();

	typedef map<StringA, StringA>::const_iterator	ParametersConstIterator;	

private:
	map<StringA, StringA>							parameters_;
	typedef pair<StringA, StringA>					ParameterPair;
	typedef map<StringA, StringA>::iterator			ParametersIterator;	
};

}

#endif // !MAPCONFIG_H__WORKSPACE__INCLUDED_
