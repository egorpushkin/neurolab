#ifndef AREAHANDLER_H__PROJECTUI__INCLUDED_
#define AREAHANDLER_H__PROJECTUI__INCLUDED_

class AreaPane;

namespace ProjectUI
{

class AreaHandler
	: public IHandler
{
public:
	AreaHandler(Workspace::IAreasProject* piAreasProject, uint areaIndex);
	virtual ~AreaHandler();

	// IHandler declarations section
	////////////////////////////////////////////////////////////////////////// 
	virtual result				Invoke();

	// ICommon declarations section
	////////////////////////////////////////////////////////////////////////// 
	virtual	ulong				AddRef();
	virtual	ulong				Release();

	virtual String				GetClassString() const;
	virtual result				QueryInterface(REFIID rIID, void** ppObject);

private:
	ulong						numRef_;

	Workspace::IAreasProject*	piAreasProject_;
	uint						areaIndex_;

	AreaPane*					pAreaPane_;

};

}

#endif // !AREAHANDLER_H__PROJECTUI__INCLUDED_
