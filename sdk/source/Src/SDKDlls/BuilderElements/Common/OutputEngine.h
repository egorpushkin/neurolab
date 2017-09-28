//	This code is a part of 'Builder Elements Component' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: OutputEngine.h
//	Description: Output engine stub.  

#ifndef OUTPUTENGINE_H__BUILDERELEMENTS__INCLUDED_
#define OUTPUTENGINE_H__BUILDERELEMENTS__INCLUDED_

//////////////////////////////////////////////////////////////////////////
// Stub constants 
//////////////////////////////////////////////////////////////////////////

// Image size for layer elements
#define SIZE_LAYER_IMAGE_WIDTH			32
#define SIZE_LAYER_IMAGE_HEIGHT			64

#define SIZE_NEURON_IMAGE_DIAMETER		20
#define SIZE_INPUT_IMAGE_DIAMETER		10

// Standart element event notifications
#define ID_REMOVE						0xff000001
#define ID_ADD_DENDRITE					0xff000002
#define ID_ADD_AXON						0xff000003
#define ID_PROPERTIES					0xff000004

// Builder control states
#define BS_NO_ACTION					0xff000000
#define BS_ZONE_SELECTING				0xff000001
#define BS_DRAGGING						0xff000002
#define	BS_CONNECTING					0xff000003

//////////////////////////////////////////////////////////////////////////
// Stub interfaces. 
//////////////////////////////////////////////////////////////////////////

// Note that this is only partial definition. You must implement full version if 
//		you are going to create your own network renderer.

// IBuilderControl declaration
interface IBuilderControl : public ICommon
{
	virtual void			SetBuilderState(uint state) = 0;
	virtual NetworkImportingKit::IElement*		
		SetActiveElement(NetworkImportingKit::IElement* piElement) = 0;
};

// IOutputDevice declaration
interface IOutputDevice : public ICommon
{
	virtual result			LoadImage(
		const String& rFileName, const String& rImageRecordName) = 0;
};

//////////////////////////////////////////////////////////////////////////
// Stub classes
//////////////////////////////////////////////////////////////////////////

// Universal point management class 
typedef struct tagBuilderPoint 
{ 
	long					x; 
	long					y; 
} BuilderPoint; 

//////////////////////////////////////////////////////////////////////////
// Stub identificators
//////////////////////////////////////////////////////////////////////////

// {f3a24b75-973f-44ee-96fa-8232e2546c72} 
DEFINE_GUID(IID_IBuilderControl, 
0xf3a24b75, 0x973f, 0x44ee, 0x96, 0xfa, 0x82, 0x32, 0xe2, 0x54, 0x6c, 0x72);

// {6404e5e3-b199-42d6-af3f-f3eef0ee8b0f} 
DEFINE_GUID(IID_IOutputDevice, 
0x6404e5e3, 0xb199, 0x42d6, 0xaf, 0x3f, 0xf3, 0xee, 0xf0, 0xee, 0x8b, 0x0f);

#endif // !OUTPUTENGINE_H__BUILDERELEMENTS__INCLUDED_
