//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: FileNameTools.cpp
//	Description: File name operations declaration.  

#include "FileNameTools.h"

StringA GetProjectName(const StringA& fileName)
{
	StringA resultName(fileName);

	StringA::size_type npos = fileName.length() + 1;

	StringA::size_type indexSlash = resultName.rfind("/", npos);
	if (indexSlash != npos)
		resultName = resultName.substr(indexSlash + 1, resultName.length() - indexSlash - 1);

	indexSlash = resultName.rfind("\\", npos);
	if (indexSlash != npos)
		resultName = resultName.substr(indexSlash + 1, resultName.length() - indexSlash - 1);

	indexSlash = resultName.rfind(".", npos);
	if (indexSlash != npos)
		resultName = resultName.substr(0, indexSlash);

	return resultName;
}

StringA GetProjectFilePath(const StringA& fileName)
{
	StringA resultPath("");

	StringA::size_type npos = fileName.length() + 1;

	StringA::size_type indexSlash = fileName.rfind("/", npos);
	if (indexSlash != npos)
		resultPath = fileName.substr(0, indexSlash + 1);

	indexSlash = fileName.rfind("\\", npos);
	if (indexSlash != npos)
		resultPath = fileName.substr(0, indexSlash + 1);

	return resultPath;
}
