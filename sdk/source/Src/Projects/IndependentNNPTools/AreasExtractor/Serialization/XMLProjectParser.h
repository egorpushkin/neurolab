#ifndef XMLPROJECTPARSER_H__SERIALIZATION__INCLUDED_
#define XMLPROJECTPARSER_H__SERIALIZATION__INCLUDED_

namespace Serialization
{

// XMLProjectParser declaration
class XMLProjectParser 
{
public:
	XMLProjectParser();
	virtual ~XMLProjectParser();

	// Public interface
	//////////////////////////////////////////////////////////////////////////
	virtual result			LoadProject(const StringA& fileName, Workspace::IAreasProject* piAreasProject);

private:
	// Private tools
	//////////////////////////////////////////////////////////////////////////
	result					ParseProject(xmlNodePtr pProjectNode, Workspace::NetworkProject* pProject);
	result					ParseImage(xmlNodePtr pImageNode, Workspace::MultispectralImage* pImage);
	result					ParseMapConfig(xmlNodePtr pMapConfigNode, Workspace::MapConfig* pMapConfig);
};

}

#endif // !XMLPROJECTPARSER_H__SERIALIZATION__INCLUDED_
