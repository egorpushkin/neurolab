//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: IBuilderElement.h
//	Description: The IBuilderElement declatarion.

#ifndef IBUILDERELEMENT_H__NETWORKIMPORTING__INCLUDED_
#define IBUILDERELEMENT_H__NETWORKIMPORTING__INCLUDED_

// IBuilderElement declatarion
interface IBuilderElement : public ICommon
{
	virtual void			SetOutputControl(
		ExternalOutputEngine::IBuilderControl* piControl) = 0;
	virtual ExternalOutputEngine::IBuilderControl*	GetOutputControl() const = 0;

	virtual void			SetElementPosition(
		const ExternalOutputEngine::BuilderPoint& point) = 0;
	virtual const ExternalOutputEngine::BuilderPoint&			
		GetElementPosition() = 0;

	virtual void			RenderElement() const = 0;

	virtual bool			IsClicked(
		const ExternalOutputEngine::BuilderPoint& point) const = 0;

	virtual void			SelectElement(bool select) = 0;
	virtual bool			IsSelected() const = 0;

	virtual void			TrackPopupMenu(
		const ExternalOutputEngine::BuilderPoint& point) const = 0;

	virtual const ExternalOutputEngine::BuilderPoint& 
		GetPositionForConnectedElement(
			const NetworkImportingKit::CConnection* pConnection) = 0;
};

#endif // !IBUILDERELEMENT_H__NETWORKIMPORTING__INCLUDED_
