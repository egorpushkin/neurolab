#ifndef PROJECTTREE_H__PROJECTUI__INCLUDED_
#define PROJECTTREE_H__PROJECTUI__INCLUDED_

namespace ProjectUI
{

interface IHandler;

class ProjectTree
{
public:
	ProjectTree();
	virtual ~ProjectTree();

	// Initialization interface
	//////////////////////////////////////////////////////////////////////////
	virtual void				SetProjectTree(CTreeCtrl* pProjectTree);
	
	// Public interface
	//////////////////////////////////////////////////////////////////////////
	virtual result				DislpayEmptyProject();
	virtual result				DislpayProject(Workspace::IAreasProject* piAreasProject);

private:
	// Private tools
	//////////////////////////////////////////////////////////////////////////
	void						ReleaseProject();
	void						CleanUpHandlers();

	// UI
	CTreeCtrl*					pProjectTree_;
	HTREEITEM					rootTreeItem_;	

	// Handlers
	vector<IHandler*>			handlersList_;	
	typedef vector<IHandler*>::iterator	HandlersIterator;
};

}

#endif // !PROJECTTREE_H__PROJECTUI__INCLUDED_
