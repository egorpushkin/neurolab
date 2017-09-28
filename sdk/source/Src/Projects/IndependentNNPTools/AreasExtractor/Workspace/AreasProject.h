#ifndef AREASPROJECT_H__WORKSPACE__INCLUDED_
#define AREASPROJECT_H__WORKSPACE__INCLUDED_

namespace Workspace
{

class AreasProject
	: public IAreasProject
{
public:
	AreasProject();
	virtual ~AreasProject();

	// IAreasProject declarations section
	////////////////////////////////////////////////////////////////////////// 
    virtual void					SetProjectName(const StringA& projectName);
	virtual StringA					GetProjectName();

	virtual MultispectralImage*		GetMultispecImage();
	virtual NetworkProject*			GetNetworkProject();
	virtual MapConfig*				GetMapConfig();
	virtual AreasHolder*			GetAreasHolder();

	virtual bool					IsBuilt();
	virtual void					SetBuilt();

	// ICommon declarations section
	////////////////////////////////////////////////////////////////////////// 
    virtual	ulong					AddRef();
	virtual	ulong					Release();

	virtual String					GetClassString() const;
	virtual result					QueryInterface(REFIID rIID, void** ppObject);

private:
	// Private tools
	////////////////////////////////////////////////////////////////////////// 
    void							CleanUp();

private:
	ulong							numRef_;

	StringA							projectName_;

	MultispectralImage*				pMultispecImage_;
	NetworkProject*					pNetworkProject_;
	MapConfig*						pMapConfig_;
	AreasHolder*					pAreasHolder_;
	
	bool							wasBuilt_;
};

}

#endif // !AREASPROJECT_H__WORKSPACE__INCLUDED_
