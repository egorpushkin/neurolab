//	This code is a part of 'Storage Processor' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: ExternalStorage.h
//	Description: External storage configuration.  

#ifndef EXTERNALSTORAGE_H__STORAGEPROCESSOR__INCLUDED_
#define EXTERNALSTORAGE_H__STORAGEPROCESSOR__INCLUDED_

// Project formats
#define FORMAT_UNEXPECTED			0x0000
#define FORMAT_SPXML10				0x0001
#define FORMAT_DEFBIN10				0x0002

// Converting methods
#define CONV_UNEXPECTED				0x0000
#define CONV_SPXML10_TO_DEFBIN10	0x0001
#define CONV_DEFBIN10_TO_SPXML10	0x0002

// Encoding settings
#define DEFAULT_STORAGE_ENCODING	"UTF-8"

// Project serialization file name constants
#define	DATA_FILE_EXTENSION			"dat"

#define	FILE_SUFFIX_ELEMENT_DATA	"ED"
#define	FILE_SUFFIX_CONNECTION_DATA	"CD"
#define	FILE_SUFFIX_CONNECTION_WEIGHTS	"CW"
#define	FILE_SUFFIX_LAYER_WEIGHTS	"LW"
#define	FILE_SUFFIX_LAYER_DELTAS	"LD"

// Flags
#define	FLAG_SECTION_LENGTH			8

#define	FLAG_ET_INPUT_OFFSET		0
#define	FLAG_ET_OUTPUT_OFFSET		8
#define	FLAG_ET_PROCESSOR_OFFSET	16
#define	FLAG_ET_CONNECTION_OFFSET	24

#define FLAG_STORE_DATA				1
#define FLAG_STORE_WEIGHTS			2
#define FLAG_STORE_DELTAS			4

// Data formats
#define DATA_FORMAT_UNEXPECTED		0x0000
#define DATA_FORMAT_PLAIN_TEXT		0x0001
#define DATA_FORMAT_TIFF			0x0002

#endif // !EXTERNALSTORAGE_H__STORAGEPROCESSOR__INCLUDED_
