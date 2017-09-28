//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: DefElement.h
//	Description: Declaring network element constants and macros.   

#ifndef DEFELEMENT_H__NETWORKIMPORTING__INCLUDED_
#define DEFELEMENT_H__NETWORKIMPORTING__INCLUDED_

//
// Connections factory types
//

#define DC_NO_FACTORY					0x00000000
#define DC_INPUTS_FACTORY				0x00000001
#define DC_OUTPUTS_FACTORY				0x00000002

//
// Network element types
//

#define ET_INPUT						0x00000003
#define ET_OUTPUT						0x00000004
#define ET_PROCESSOR					0x00000005
#define ET_CONNECTION					0x00000008

#define ET_DATAFLOW						0x00000007
#define ET_ELEMENT						0x00000007
#define ET_OBJECT						0x00000007

#define ET_BENCHMARK					0xff000006

#endif // !DEFELEMENT_H__NETWORKIMPORTING__INCLUDED_
