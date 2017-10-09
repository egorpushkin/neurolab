#include "stdafx.h"

#include "../../Interfaces/IHandler.h"
#include "AreaHandler.h"

#include "../../../AreasBuilder.h"
#include "../ProjectPanes/AreaPane.h"

namespace ProjectUI
{

AreaHandler::AreaHandler(Workspace::IAreasProject* piAreasProject, uint areaIndex)
	: numRef_(0)
	, piAreasProject_(piAreasProject)
	, areaIndex_(areaIndex)
	, pAreaPane_(NULL)
{
	assert(piAreasProject_ != NULL);
	piAreasProject_->AddRef();
}

AreaHandler::~AreaHandler()
{
	piAreasProject_->Release();

	if (pAreaPane_)		
		pAreaPane_->DestroyWindow();

	delete pAreaPane_;
}

// IHandler implementations section
////////////////////////////////////////////////////////////////////////// 
result AreaHandler::Invoke()
{
	if (!piAreasProject_->IsBuilt())
	{
		AfxMessageBox(_T("You must buld project before displaying areas."));
		return S_FALSE;
	}	

	if (!pAreaPane_)
	{
		char panelName[MAX_PATH];
		sprintf(panelName, "Area Panel: %d", areaIndex_);

		pAreaPane_ = new AreaPane(piAreasProject_, areaIndex_);
		pAreaPane_->Create(panelName, WS_CHILD | WS_VISIBLE, AfxGetMainWnd(), IDC_PP_AREA_WINDOW + areaIndex_);
		pAreaPane_->SetBarStyle(pAreaPane_->GetBarStyle() |
			CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
		pAreaPane_->EnableDocking(0);
		((CMDIFrameWnd*)AfxGetMainWnd())->DockControlBar(pAreaPane_, AFX_IDW_DOCKBAR_TOP);
		pAreaPane_->OnNcLButtonDblClk(0, CPoint(0, 0));
		pAreaPane_->StyleDispl(GuiDrawLayer::m_Style);

	} else 
		((CGuiMDIFrame*)AfxGetMainWnd())->ShowHideBar(pAreaPane_);		

	return S_OK;
}

// ICommon implementations section
ulong AreaHandler::AddRef()
{
	return ++numRef_;						
}

ulong AreaHandler::Release()
{
	--numRef_;

	if (numRef_ == 0)
	{
		delete this;
		return 0;
	}

	return numRef_;
}

String AreaHandler::GetClassString() const
{
	return _T("AreaHandler");
}

result AreaHandler::QueryInterface(REFIID rIID, void** ppObject)
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
