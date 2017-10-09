//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IStructureBuilder.h
//	Description: The IStructureBuilder declaration.

#ifndef ISTRUCTUREBUILDER_H__NETWORKIMPORTING__INCLUDED_
#define ISTRUCTUREBUILDER_H__NETWORKIMPORTING__INCLUDED_

// IStructureBuilder declaration
interface IStructureBuilder : public ICommon
{
	// Construction routines
	virtual IElement*		AddElement(const StringA& sysName, bool registerElement = true) = 0;	
	virtual result			ConnectElements(IElement* piElementSrc, IElement* piElementDest, uint connectionSize = 1) = 0;
	virtual CConnection*	CreateConnection(uint connectionSize = 1) = 0;

	// Serialization helpers
	virtual void			EstablishConnections() = 0;

	// Initialization helpers
	virtual result			ApplyTransferFunction(IElement* piElement, const StringA& functionName) = 0;
	virtual result			LocateElement(IElement* piElement, uint positionX, uint positionY) = 0;

	// Distruction routines
	virtual	result			RemoveElement(IElement* piElement) = 0;
	virtual result			DisconnectElements(IElement* piElementSrc, IElement* piElementDest, bool removeAllConnections = true) = 0;
	virtual	result			ReleaseContent() = 0;
};

#endif // !ISTRUCTUREBUILDER_H__NETWORKIMPORTING__INCLUDED_
