//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: PGMSerialization.cpp
//	Description: PGM files serialization routines implementasion.

#include "../../Headers/CmnDataProcessingLib.h"

using namespace DataProcessingKit;

// Serialization tools
result PGMBReadHeader(FILEDev& FileDev, int* XSize, int* YSize, unsigned char* MaxG)
{
	int				count;
	char			line[255];
	int				maxg2;
	char*			next;
	int				step;
	int				width;
	char			word[255];

	step = 0;

	bool bFinishCondition = true;
	while (bFinishCondition)
	{
		bool bRead = FileDev.ReadStringA(line, sizeof(line));

		if (!bRead)
			return STG_E_INVALIDHEADER;

		next = line;

		if (line[0] == '#')
			continue;

		if (step == 0)
		{
			count = sscanf(next, "%s%n", word, &width);
			if (count == EOF)
				continue;

			next = next + width;
			if (strcmp(word, "P5") != 0 && strcmp(word, "p5") != 0)
				return false;

			step = 1;
		}

		if ( step == 1 )
		{
			count = sscanf(next, "%d%n", XSize, &width);
			next = next + width;

			if (count == EOF)
				continue;

			step = 2;
		}

		if (step == 2)
		{
			count = sscanf(next, "%d%n", YSize, &width);
			next = next + width;

			if (count == EOF)
				continue;

			step = 3;
		}

		if (step == 3)
		{
			count = sscanf(next, "%d%n", &maxg2, &width);
			*MaxG = (unsigned char)maxg2;
			next = next + width;

			if (count == EOF)
				continue;

			break;
		}
	}

	return S_OK;
}
