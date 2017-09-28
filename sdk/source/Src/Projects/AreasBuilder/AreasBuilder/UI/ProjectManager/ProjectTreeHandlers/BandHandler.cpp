#include "stdafx.h"

#include "../../Interfaces/IHandler.h"
#include "BandHandler.h"

#include "../../../AreasBuilder.h"
#include "../ProjectPanes/BandPane.h"

namespace ProjectUI
{

BandHandler::BandHandler(Workspace::IAreasProject* piAreasProject, Workspace::Band* pBand)
	: numRef_(0)
	, piAreasProject_(piAreasProject)
	, pBand_(pBand)
	, pBandPane_(NULL)
{
	assert(piAreasProject_ != NULL);
	assert(pBand != NULL);

	piAreasProject_->AddRef();
}

BandHandler::~BandHandler()
{
	piAreasProject_->Release();

	if (pBandPane_)		
		pBandPane_->DestroyWindow();

	delete pBandPane_;
}

// IHandler implementations section
////////////////////////////////////////////////////////////////////////// 
result BandHandler::Invoke()
{
	if (!pBandPane_)
	{
		StringA panelName = 
			StringA(_T("Band Panel: ")) + 
			pBand_->GetBandName();

		pBandPane_ = new BandPane(piAreasProject_, pBand_);
		pBandPane_->Create(panelName.c_str(), WS_CHILD | WS_VISIBLE, AfxGetMainWnd(), IDC_PP_BAND_WINDOW);
		pBandPane_->SetBarStyle(pBandPane_->GetBarStyle() |
			CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
		pBandPane_->EnableDocking(0);
		((CMDIFrameWnd*)AfxGetMainWnd())->DockControlBar(pBandPane_, AFX_IDW_DOCKBAR_TOP);
		pBandPane_->OnNcLButtonDblClk(0, CPoint(0, 0));
		pBandPane_->StyleDispl(GuiDrawLayer::m_Style);

	} else 
		((CGuiMDIFrame*)AfxGetMainWnd())->ShowHideBar(pBandPane_);

	return S_OK;
}

// ICommon implementations section
ulong BandHandler::AddRef()
{
	return ++numRef_;						
}

ulong BandHandler::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String BandHandler::GetClassString() const
{
	return _T("BandHandler");
}

result BandHandler::QueryInterface(REFIID rIID, void** ppObject)
{
	if (rIID == IID_ICommon)
	{		
		*ppObject = static_cast<ICommon*>(this);
	}
	if (rIID == IID_IHandler)
	{		
		*ppObject = static_cast<IHandler*>(this);
	}
	else
	{
		*ppObject = NULL;
		return E_NOINTERFACE;
	}

	static_cast<ICommon*>(this)->AddRef();
	return S_OK;
}

}
