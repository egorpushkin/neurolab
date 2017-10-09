//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: StorageFlags.h
//	Description: Processing flags.  

#ifndef STORAGEFLAGS_H__STORAGEPROCESSOR__INCLUDED_
#define STORAGEFLAGS_H__STORAGEPROCESSOR__INCLUDED_

class FlagsProcessor
{
public:
	// Set
	static dword Prepare(dword flagPosition, dword value)
	{
		return value << flagPosition; 
	}

	// Receive
	static dword GetSection(dword flags, dword sectionPosition)
	{
		dword resultValue = flags;

		dword totalBits = sizeof(dword) * 8;

		if (sectionPosition + FLAG_SECTION_LENGTH < totalBits)
			resultValue = resultValue << (totalBits - (sectionPosition + FLAG_SECTION_LENGTH));

		resultValue = resultValue >> (totalBits - FLAG_SECTION_LENGTH);

		return resultValue;
	}

	static bool IsSet(dword flags, dword sectionPosition, dword flag)
	{
		dword section = GetSection(flags, sectionPosition);
		dword res = section & flag;
		
		return (res != 0x0);
	}
};


#endif // !STORAGEFLAGS_H__STORAGEPROCESSOR__INCLUDED_
