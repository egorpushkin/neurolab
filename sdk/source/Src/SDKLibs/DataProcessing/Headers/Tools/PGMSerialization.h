//	This code is a part of 'Data Processing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: PGMSerialization.h
//	Description: PGM files serialization routines definition.

// Serialization tools
result PGMBReadHeader(DataProcessingKit::FILEDev& FileDev, int* XSize, int* YSize, unsigned char* MaxG);

template<typename T> 
result PGMReadData(DataProcessingKit::FILEDev& FileDev, int XSize, int YSize, T* Data)
{
	unsigned char		c;
	int					i;
	int					j;

	for (j = 0; j < YSize; j++)
		for (i = 0; i < XSize; i++)
		{
			size_t iread = FileDev.Read(&c, 1);
			*Data = (T)c;
			Data = Data + 1;

			if (iread < 1)
				return STG_E_INVALIDFORMAT;
		}

		return S_OK;
}
