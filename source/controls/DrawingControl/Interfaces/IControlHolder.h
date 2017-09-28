#ifndef IDRAWINGCONTROL_H__DRAWINGCONTROL__INCLUDED_
#define IDRAWINGCONTROL_H__DRAWINGCONTROL__INCLUDED_

namespace DrawingControl
{

	interface IControlHolder : public MinCOM::ICommon
	{

		virtual void SetBorder(uint border) = 0;

		virtual result DisplayControl() = 0;
		virtual result CloseControl() = 0;


		virtual IDrawingControlPtr GetDrawingControl() = 0;

	};

	// {f1f48ae3-2624-401c-87c7-9f8a8ae7e365} 
	DEFINE_GUID(IID_IControlHolder, 
	0xf1f48ae3, 0x2624, 0x401c, 0x87, 0xc7, 0x9f, 0x8a, 0x8a, 0xe7, 0xe3, 0x65);

	typedef MinCOM::ComPtr< IControlHolder > IControlHolderPtr;
	typedef const IControlHolderPtr& IControlHolderRef;

}

#endif // !IDRAWINGCONTROL_H__DRAWINGCONTROL__INCLUDED_
