#include "PrecompiledHeader.h"

#include "AreasTool.h"

#include "Serializer.h"

namespace Areas
{

	Serializer::Serializer()
	{	
	}

	Serializer::~Serializer()
	{	
	}

	// Public interface
	result Serializer::LoadAreas(const StringA& fileName, AreasTool* pAreas)
	{
		if ( !pAreas )
			return E_FAIL;

		// Open file
		FILEDev fileDev;
		if ( FAILED(fileDev.Open(fileName.c_str(), ModeRead)) )
			return E_FAIL;

		// Parsing file format begin
		//////////////////////////////////////////////////////////////////////////
		char buffer[MAX_BUFFER_LENGTH];
		
		// Skip comments line
		fgets(buffer, MAX_BUFFER_LENGTH, fileDev);

		// Read a number of areas
		uint areasCount = 0;
		if ( !fscanf(fileDev, "%d", &areasCount) )
			return E_FAIL;

		// Go to the next line
		fgets(buffer, MAX_BUFFER_LENGTH, fileDev);

		if ( !areasCount ) 
			return E_FAIL;

		pAreas->AllocateAreas(areasCount);

		// Skip comments line
		fgets(buffer, MAX_BUFFER_LENGTH, fileDev);

		// Reading areas
		for ( uint i = 0 ; i < areasCount ; ++i )
		{
			// Skip comments line
			fgets(buffer, MAX_BUFFER_LENGTH, fileDev);

			// Skip area's name
			fgets(buffer, MAX_BUFFER_LENGTH, fileDev);

			// Skip comments line
			fgets(buffer, MAX_BUFFER_LENGTH, fileDev);

			// Read a number of points
			uint pointsCount = 0;
			if ( !fscanf(fileDev, "%d", &pointsCount) )
				return E_FAIL;

			// Go to the next line
			fgets(buffer, MAX_BUFFER_LENGTH, fileDev);

			pAreas->AllocateArea(i, pointsCount);

			// Skip comments line
			fgets(buffer, MAX_BUFFER_LENGTH, fileDev);

			// Reading points
			for ( uint j = 0 ; j < pointsCount ; ++j )
			{
				// Read point's coordinates
				uint x = 0, y = 0;
				if ( !fscanf(fileDev, "%d", &x) )
					return E_FAIL;
				if ( !fscanf(fileDev, "%d", &y) )
					return E_FAIL;

				pAreas->SetAreaPoint(i, j, x, y);
			}
			
			// Calculating area boundary
			pAreas->CalcBoundary(i);

			// Go to the next line
			fgets(buffer, MAX_BUFFER_LENGTH, fileDev);
		}

		return S_OK;
	}

}
