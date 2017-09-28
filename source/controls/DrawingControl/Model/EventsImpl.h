#ifndef EVENTSIMPL_H__DRAWINGCONTROL__INCLUDED_
#define EVENTSIMPL_H__DRAWINGCONTROL__INCLUDED_

namespace DrawingControl
{

	class EventsImpl 
		: public MinCOM::CommonImpl< IEvents > 
	{
	public:

		EventsImpl() {}
		virtual ~EventsImpl() {}

		// IEvents section
		virtual void OnInit()
		{
		}

		virtual void OnPaint(Gdiplus::Graphics* /* pGraphics */)
		{
		}

		virtual void OnSize(uint /* type */, int /* cx */, int /* cy */)
		{			
		}

		virtual bool OnMouseWheel(uint /* flags */, short /* delta */, const CPoint& /* pt */)
		{
            return false;
		}

		virtual void OnLButtonDown(uint /* flags */, const CPoint& /* point */)
		{
		}

		virtual void OnLButtonUp(uint /* flags */, const CPoint& /* point */)
		{
		}

		virtual void OnMouseMove(uint /* flags */, const CPoint& /* point */)
		{
		}

		virtual void OnTimer(uint /* nIDEvent */)
		{
		}

		// ICommon section
		virtual result QueryInterface(REFIID iid, void** ppObject)
		{
			if ( iid == MinCOM::IID_ICommon )
				*ppObject = static_cast< MinCOM::ICommon* >(this);

			else if ( iid == IID_IEvents )
				*ppObject = static_cast< IEvents* >(this);

			else
			{
				*ppObject = NULL;
				return E_NOINTERFACE;
			}

			static_cast< MinCOM::ICommon* >(this)->AddRef();
			return S_OK;
		}

	};

}

#endif // !EVENTSIMPL_H__DRAWINGCONTROL__INCLUDED_
