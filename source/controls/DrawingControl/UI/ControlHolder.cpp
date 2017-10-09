#include "Common/stdafx.h"

#include "ControlHolder.h"

#include "DrawingCtrl.h"
#include ".\controlholder.h"

namespace DrawingControl
{

	IMPLEMENT_DYNAMIC(ControlHolder, CDialog)
	ControlHolder::ControlHolder(CWnd* pParent /*=NULL*/)
		: CDialog(ControlHolder::IDD, pParent)
		, drawingControl_(new DrawingCtrl, IID_IDrawingControl)
		, border_(0)
	{
	}

	ControlHolder::~ControlHolder()
	{
		if ( m_hWnd )
		{
			SendMessage(WM_CLOSE);
		}
	}

	void ControlHolder::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
	}

	BEGIN_MESSAGE_MAP(ControlHolder, CDialog)
		ON_WM_SIZE()
	END_MESSAGE_MAP()

	BOOL ControlHolder::OnInitDialog()
	{
		CDialog::OnInitDialog();

		CRect rect;
		GetClientRect(&rect);
		rect.InflateRect(-1 * border_, -1 * border_);

		drawingControl_->Create(this, rect);     

		return TRUE; 
	}

	void DrawingControl::ControlHolder::OnSize(UINT nType, int cx, int cy)
	{
		CDialog::OnSize(nType, cx, cy);

        if ( m_hWnd && drawingControl_ ) 
		{
			CRect rect(0, 0, cx, cy);
			rect.InflateRect(-1 * border_, -1 * border_);

            drawingControl_->Move(rect);
		}	
	}

	// IControlHolder section
	void ControlHolder::SetBorder(uint border)
	{
		border_ = border;
	}

	result ControlHolder::DisplayControl()
	{
		IControlHolderPtr thisControl(this, IID_IControlHolder);
		
		INT_PTR retCode = CDialog::DoModal();
		return ( retCode == IDOK ) ? ( S_OK ) : ( S_FALSE );
	}

	result ControlHolder::CloseControl()
	{
		if ( !m_hWnd )
			return E_FAIL;

		::SendMessage(m_hWnd, WM_CLOSE, 0, 0);
		return S_OK;
	}

	IDrawingControlPtr ControlHolder::GetDrawingControl()
	{
		return drawingControl_;
	}

	// ICommon section
	result ControlHolder::QueryInterface(REFIID iid, void** ppObject)
	{
		if ( iid == MinCOM::IID_ICommon )
			*ppObject = static_cast< MinCOM::ICommon* >(this);

		else if ( iid == IID_IControlHolder )
			*ppObject = static_cast< IControlHolder* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		static_cast< MinCOM::ICommon* >(this)->AddRef();
		return S_OK;
	}

}

