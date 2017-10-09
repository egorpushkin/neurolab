#ifndef IAREASPROJECT_H__WORKSPACE__INCLUDED_
#define IAREASPROJECT_H__WORKSPACE__INCLUDED_

namespace Workspace
{

// {3d474b82-9a7a-4600-aa8e-7af4a45731a7} 
DEFINE_GUID(IID_IAreasProject, 
0x3d474b82, 0x9a7a, 0x4600, 0xaa, 0x8e, 0x7a, 0xf4, 0xa4, 0x57, 0x31, 0xa7);

interface IAreasProject : public ICommon
{
	virtual void					SetProjectName(const StringA& projectName) = 0;
	virtual StringA					GetProjectName() = 0;

	virtual MultispectralImage*		GetMultispecImage() = 0;				
	virtual NetworkProject*			GetNetworkProject() = 0;
	virtual MapConfig*				GetMapConfig() = 0;
	virtual AreasHolder*			GetAreasHolder() = 0;

	virtual bool					IsBuilt() = 0;
	virtual void					SetBuilt() = 0;
};

}

#endif // !IAREASPROJECT_H__WORKSPACE__INCLUDED_
