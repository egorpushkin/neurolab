#include "../PrecompiledHeader.h"

#include "AreasExporter.h"

using namespace Workspace;

namespace Serialization
{

// Public interface
//////////////////////////////////////////////////////////////////////////
result AreasExporter::ExportAreas(Workspace::IAreasProject* piAreasProject) const
{
	const uint width = piAreasProject->GetAreasHolder()->GetMapWidth();
	const uint height = piAreasProject->GetAreasHolder()->GetMapHeight();
    
	for (uint i = 0;i < piAreasProject->GetAreasHolder()->GetAreasCount();i++)
	{
		const result res = ExportArea(i, piAreasProject->GetAreasHolder()->GetArea(i), width, height);
		if (FAILED(res))
			return res;
	}

	return S_OK;
}

// Private tools
//////////////////////////////////////////////////////////////////////////
result AreasExporter::ExportArea(const uint classIndex, IDataFactory* piMapData, const uint width, const uint height) const
{
	IDataFactory* piIntermObject = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
	piIntermObject->SetData(piMapData);

	const float minRange = 0.0f;
	const float maxRange = 1.0f;
	const float scale = 255.0f;

	for (uint i = 0;i < piIntermObject->GetDataLength();i++)
	{
		const float value = piIntermObject->GetItemData(i);
		const float prepared = (value - minRange)/(maxRange - minRange) * scale;
		piIntermObject->SetItemData(i, prepared);
	}

	char fileNamePostf[MAX_PATH];
	sprintf(fileNamePostf, "%d", classIndex);
	StringA fileName = 
		StringA("Class") + 
		StringA(fileNamePostf) + 
		StringA(".pgm");

	CPGMBitmap pgmBitmap; 
	pgmBitmap.ConstructFromDataFactory(piIntermObject, width, height);
	pgmBitmap.SavePGMBitmap(fileName.c_str());
	
	piIntermObject->Release();

	return S_OK;
}

}
