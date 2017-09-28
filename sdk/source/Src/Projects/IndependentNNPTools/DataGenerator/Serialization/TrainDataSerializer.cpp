#include "PrecompiledHeader.h"

#include "TrainDataSerializer.h"

namespace Serialization
{

	result TrainDataSerializer::StoreData(const StringA& fileName, IDataFile* piDataFile)
	{
		FILEDev fileDev;
		if ( FAILED(fileDev.Open(fileName.c_str(), ModeWrite)) )
			return E_FAIL;

        fprintf(fileDev, "%d %d %d\n", 
			piDataFile->GetInputSymbolsCount(), 
			piDataFile->GetInputSymbolLength(),
			piDataFile->GetOutputSymbolLength());

		for (uint i = 0 ; i < piDataFile->GetInputSymbolsCount() ; ++i )
		{
			for ( uint j = 0 ; j < piDataFile->GetInputSymbolLength() ; ++j )
			{
				fprintf(fileDev, "%f ", piDataFile->GetInputSymbol(i)->GetItemData(j));				
			}
			fprintf(fileDev, "\n");				

			for ( uint j = 0 ; j < piDataFile->GetOutputSymbolLength() ; ++j )
			{
				fprintf(fileDev, "%f ", piDataFile->GetOutputSymbol(i)->GetItemData(j));				
			}
			fprintf(fileDev, "\n");				
		}        

		return S_OK;
	}

}
