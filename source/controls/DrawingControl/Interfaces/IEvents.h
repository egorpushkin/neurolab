#ifndef IEVENTS_H__DRAWINGCONTROL__INCLUDED_
#define IEVENTS_H__DRAWINGCONTROL__INCLUDED_

namespace DrawingControl
{

	interface IEvents : public MinCOM::ICommon
	{

		virtual void OnInit() = 0;	
		virtual void OnPaint(Gdiplus::Graphics* pGraphics) = 0;
		virtual void OnSize(uint type, int cx, int cy) = 0;
		virtual bool OnMouseWheel(uint flags, short delta, const CPoint& pt) = 0;
		virtual void OnLButtonDown(uint flags, const CPoint& point) = 0;
		virtual void OnLButtonUp(uint flags, const CPoint& point) = 0;
		virtual void OnMouseMove(uint flags, const CPoint& point) = 0;
		virtual void OnTimer(uint nIDEvent) = 0;			

	};

	// {97d8b1fd-c5e8-4f3e-b5fc-7561f6fa41da} 
	DEFINE_GUID(IID_IEvents, 
	0x97d8b1fd, 0xc5e8, 0x4f3e, 0xb5, 0xfc, 0x75, 0x61, 0xf6, 0xfa, 0x41, 0xda);

	typedef MinCOM::ComPtr< IEvents > IEventsPtr;
	typedef const IEventsPtr& IEventsRef;

}

#endif // !IEVENTS_H__DRAWINGCONTROL__INCLUDED_
