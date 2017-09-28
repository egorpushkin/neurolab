#ifndef AREASHOLDER_H__WORKSPACE__INCLUDED_
#define AREASHOLDER_H__WORKSPACE__INCLUDED_

namespace Workspace
{

class AreasHolder
{
public:
	AreasHolder();
	virtual ~AreasHolder();

	// Public interface
	////////////////////////////////////////////////////////////////////////// 
    virtual void			AddArea(IDataFactory* piFactory);
	virtual IDataFactory* 	GetArea(uint index);
	virtual size_t		 	GetAreasCount();

    virtual void			SetMapDetails(uint width, uint height);
	virtual uint			GetMapWidth();
	virtual uint			GetMapHeight();

	virtual void			ReleaseAreas();

private:
	vector<IDataFactory*>	areasVector_;

	uint					mapWidth_;
	uint					mapHeight_;
};

}

#endif // !AREASHOLDER_H__WORKSPACE__INCLUDED_
