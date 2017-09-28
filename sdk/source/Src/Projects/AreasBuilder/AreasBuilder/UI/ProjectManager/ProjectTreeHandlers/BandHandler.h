#ifndef BANDHANDLER_H__PROJECTUI__INCLUDED_
#define BANDHANDLER_H__PROJECTUI__INCLUDED_

class BandPane;

namespace ProjectUI
{

class BandHandler
	: public IHandler
{
public:
	BandHandler(Workspace::IAreasProject* piAreasProject, Workspace::Band* pBand);
	virtual ~BandHandler();

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
	Workspace::Band*			pBand_;

	BandPane*					pBandPane_;

};

}

#endif // !BANDHANDLER_H__PROJECTUI__INCLUDED_
