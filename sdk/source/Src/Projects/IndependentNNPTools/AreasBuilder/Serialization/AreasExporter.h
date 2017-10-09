#ifndef AREASEXPORTER_H__SERIALIZATION__INCLUDED_
#define AREASEXPORTER_H__SERIALIZATION__INCLUDED_

namespace Serialization
{

// AreasExporter declaration
class AreasExporter 
{
public:
	// Public interface
	//////////////////////////////////////////////////////////////////////////
	virtual result			ExportAreas(Workspace::IAreasProject* piAreasProject) const;

private:
	// Private tools
	//////////////////////////////////////////////////////////////////////////
	virtual result			ExportArea(const uint classIndex, IDataFactory* piMapData, const uint width, const uint height) const;

};

}

#endif // !AREASEXPORTER_H__SERIALIZATION__INCLUDED_
