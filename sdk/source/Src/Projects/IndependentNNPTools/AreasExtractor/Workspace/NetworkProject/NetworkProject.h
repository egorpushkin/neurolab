#ifndef NETWORKPROJECT_H__WORKSPACE__INCLUDED_
#define NETWORKPROJECT_H__WORKSPACE__INCLUDED_

namespace Workspace
{

class NetworkProject
{
public:
	NetworkProject();
	virtual ~NetworkProject();

	virtual result			LoadProject(const StringA& fileName, const StringA& project);	

	virtual NetworkImportingKit::INetworkProcessor* GetProcessor();
	virtual StringA			GetFileName();	
	virtual StringA			GetProjectName();	

private:
	// Private tools
	//////////////////////////////////////////////////////////////////////////
    void					CleanUp();

	// Members
	//////////////////////////////////////////////////////////////////////////
	ConsoleHelpersKit::NetworkImportHelper			netHelper_;

	NetworkImportingKit::INetworkProcessor*			piNetProc_;
	StringA					fileName_;
	StringA					projectName_;
};

}

#endif // !NETWORKPROJECT_H__WORKSPACE__INCLUDED_
