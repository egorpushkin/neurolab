#ifndef CONTROLHOLDER_H__DRAWINGCONTROL__INCLUDED_
#define CONTROLHOLDER_H__DRAWINGCONTROL__INCLUDED_

namespace DrawingControl
{

	class ControlHolder 
		: public CDialog
		, public MinCOM::CommonImpl< IControlHolder > 
	{

		DECLARE_DYNAMIC(ControlHolder)

	public:

		ControlHolder(CWnd* pParent = NULL);   // standard constructor
		virtual ~ControlHolder();

		// IControlHolder section
		virtual void SetBorder(uint border);

		virtual result DisplayControl();
		virtual result CloseControl();

		virtual IDrawingControlPtr GetDrawingControl();

		// ICommon section
		virtual result QueryInterface(REFIID iid, void** ppObject);

	protected:

		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		virtual BOOL OnInitDialog();

		afx_msg void OnSize(UINT nType, int cx, int cy);

		DECLARE_MESSAGE_MAP()

	private:

		// Dialog Data
		enum { IDD = IDD_DRAWING_CTRL_DLG };

	private:

		IDrawingControlPtr drawingControl_;

		uint border_;

	};

}

#endif // !CONTROLHOLDER_H__DRAWINGCONTROL__INCLUDED_
