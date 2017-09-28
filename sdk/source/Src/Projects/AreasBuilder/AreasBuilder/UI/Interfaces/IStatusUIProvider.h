#ifndef ISTATUSUIPROVIDER_H__PROJECTUI__INCLUDED_
#define ISTATUSUIPROVIDER_H__PROJECTUI__INCLUDED_

namespace ProjectUI
{

// {befd4ce0-29c0-4265-b1ce-678ef838b313} 
DEFINE_GUID(IID_IStatusUIProvider, 
0xbefd4ce0, 0x29c0, 0x4265, 0xb1, 0xce, 0x67, 0x8e, 0xf8, 0x38, 0xb3, 0x13);

interface IStatusUIProvider : public ICommon
{
	virtual void			SetAreasProject(Workspace::IAreasProject* piAreasProject) = 0;
	virtual void			SetProjectManager(ProjectUI::ProjectManager* pProjectManager) = 0;

	virtual INT_PTR			ShowModalDialog() = 0;
	virtual void			CloseModalDialog() = 0;
	virtual void			InitialUpdateUI() = 0;
	virtual void			AllowCloseDialog() = 0;

	virtual void			UpdatePercentage(uint percentage) = 0;
};

}

#endif // !ISTATUSUIPROVIDER_H__PROJECTUI__INCLUDED_
