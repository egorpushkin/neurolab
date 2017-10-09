#ifndef PROJECTMANAGER_H__PROJECTUI__INCLUDED_
#define PROJECTMANAGER_H__PROJECTUI__INCLUDED_

namespace ProjectUI
{

class ProjectTree;
interface IStatusUIProvider;
interface ILogOutputManager;

class ProjectManager
{
public:
	ProjectManager();
	virtual ~ProjectManager();

	// Initialization interface
	//////////////////////////////////////////////////////////////////////////
	virtual void						SetProjectTree(CTreeCtrl* pProjectTree);
	virtual void						SetLogOutputManager(ILogOutputManager* piLogOutputManager);

	// Public interface. Common
	//////////////////////////////////////////////////////////////////////////
	virtual result						DisplayLogMessage(const String& providerName, const String& message);
	virtual result						ClearLog(const String& providerName);

	// Public interface. Builder engine
	//////////////////////////////////////////////////////////////////////////
	virtual void						SetLastError(result errorCode);
	virtual result						GetLastError();

	virtual IStatusUIProvider*			GetStatusProvider();
	virtual Workspace::IAreasProject*	GetAreasProject();

	// Public interface. Application UI
	//////////////////////////////////////////////////////////////////////////
	virtual result						DislpayEmptyProject();
	virtual result						DislpayProject(Workspace::IAreasProject* piAreasProject);
	virtual result						BuildDisplayedProject();

	// Public interface. Status dialog
	//////////////////////////////////////////////////////////////////////////
	virtual	void						ResumeBuilding();
	virtual	void						SetTerminationFlag(bool terminate);
	virtual LONG						IsTerminationFlagSet();

private:
	// Project model
	Workspace::IAreasProject*			piAreasProject_;
	
	// UI conrols and management tools
	ProjectTree*						pProjectTreeManager_;
	ILogOutputManager*					piLogOutputManager_;

	// Building temporaries	
	handle								buildThreadHandle_;
	IStatusUIProvider*					piCurrentStatusProvider_;
	result								errorCode_;
	LONG								terminateImmediately_;
};

}

#endif // !PROJECTMANAGER_H__PROJECTUI__INCLUDED_
