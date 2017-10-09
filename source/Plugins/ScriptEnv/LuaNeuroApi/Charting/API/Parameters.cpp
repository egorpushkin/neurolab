#include "StdAfx.h"
#include "Charting.h"

#include "..\..\GlobalStorage.h"
#include "..\..\ApiMacro.h"

#include "../../../ScriptEnv.h"
#include "../ui/ChartsViewDlg.h"

int	LuaCharting_SetAxesRanges(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)	

	POP_ARGUMENT(CChartsViewDlg*, pChartsView, 1)
	float rangeX_ = (float)lua_tonumber(L, 2);
	float rangeY_ = (float)lua_tonumber(L, 3);

	Simple2dCharting::ChartToolPtr chartTool = pChartsView->chartCtrl_.GetChart("axes");

    Simple2dCharting::AxisRenderer* pAxisRenderer = 
		dynamic_cast< Simple2dCharting::AxisRenderer* >(chartTool->GetRenderer().GetPointer());

	Simple2dCharting::AxisRenderer::Parameters params = pAxisRenderer->GetParameters();
	params.rangeX_ = rangeX_;
	params.rangeY_ = rangeY_;
	pAxisRenderer->SetParameters(params);	
	
	pChartsView->SafeInvalideteChart();

    return 0;
}

int LuaCharting_SetScale(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)	

	POP_ARGUMENT(CChartsViewDlg*, pChartsView, 1)
	float scaleX_ = (float)lua_tonumber(L, 2);
	float scaleY_ = (float)lua_tonumber(L, 3);

	pChartsView->chartCtrl_.GetCartesians()->SetScaleX(scaleX_);
	pChartsView->chartCtrl_.GetCartesians()->SetScaleY(scaleY_);

	pChartsView->SafeInvalideteChart();

    return 0;
}
