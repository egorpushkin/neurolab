#ifndef ICONTROLHOLDER_H__DRAWINGCONTROL__INCLUDED_
#define ICONTROLHOLDER_H__DRAWINGCONTROL__INCLUDED_

namespace DrawingControl
{

	interface IDrawingControl : public MinCOM::ICommon
	{
		
		virtual result Create(CWnd* pParent, const CRect& rect) = 0;
		virtual result Move(const CRect& rect) = 0;

		virtual result SetEventsHandler(IEvents* events) = 0;

        virtual void SetTimer(uint id, dword elapse) = 0;
		virtual void KillTimer(uint id) = 0;

        virtual void Repaint() = 0;

	};

	// {c94bb6b5-feab-46e1-8c9e-eaf301883b1f} 
	DEFINE_GUID(IID_IDrawingControl, 
	0xc94bb6b5, 0xfeab, 0x46e1, 0x8c, 0x9e, 0xea, 0xf3, 0x01, 0x88, 0x3b, 0x1f);

	typedef MinCOM::ComPtr< IDrawingControl > IDrawingControlPtr;
	typedef const IDrawingControlPtr& IDrawingControlRef;

}

#endif // !ICONTROLHOLDER_H__DRAWINGCONTROL__INCLUDED_
