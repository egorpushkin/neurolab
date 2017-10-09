#include "../../PrecompiledHeader.h"

#include "AreasHolder.h"

namespace Workspace
{

AreasHolder::AreasHolder()
	: areasVector_()
	, mapWidth_(0)
	, mapHeight_(0)
{
}

AreasHolder::~AreasHolder()
{
	for (uint i = 0;i < areasVector_.size();i++)
		areasVector_.at(i)->Release();	
}

// Public interface
////////////////////////////////////////////////////////////////////////// 
void AreasHolder::AddArea(IDataFactory* piFactory)
{
	assert(piFactory != NULL);

	piFactory->AddRef();
	areasVector_.push_back(piFactory);
}

IDataFactory* AreasHolder::GetArea(uint index)
{
	if (areasVector_.size() <= index)
		return NULL;

	return areasVector_.at(index);	
}

size_t AreasHolder::GetAreasCount()
{
	return areasVector_.size();
}

void AreasHolder::SetMapDetails(uint width, uint height)
{
	mapWidth_ = width;
	mapHeight_ = height;
}

uint AreasHolder::GetMapWidth()
{
	return mapWidth_;
}

uint AreasHolder::GetMapHeight()
{
	return mapHeight_;
}

}
