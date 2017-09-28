#include "StdAfx.h"
#include "Training.h"

#include "..\..\..\..\ApiMacro.h"
#include "..\..\..\..\GlobalStorage.h"

#include "../Engine/fann.h"

int TrainCallBack(unsigned int epochs, float error)
{
	CString tmMessage1(_T("N"));
	CString tmMessage2;
	tmMessage2.Format(_T("The MSE is %f after %d epoch(s)."), error, epochs);
	CString tmMessage3(_T("TrainCallBack"));

	CLuaStorage_LogProvider::pLogProvider->AddLogMessage(
		tmMessage1,
		tmMessage2,
		tmMessage3);	
	
	return 1;
}

int LuaFann121_TrainOnFannData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(4)

	POP_ARGUMENT(fann*, pAnn, 1)
	POP_ARGUMENT(fann_train_data*, pTrainData, 2)
	unsigned int maxEpochs = (unsigned int)lua_tonumber(L, 3);
	unsigned int epochsBetweenReports = (unsigned int)lua_tonumber(L, 4);
	float desiredError = (float)lua_tonumber(L, 5);

	fann_train_on_data_callback(pAnn, pTrainData, maxEpochs, epochsBetweenReports, desiredError, TrainCallBack);

	return true;
}

int LuaFann121_ClearTrainArrays(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1)

	fann_clear_train_arrays(pAnn);

	return true;
}

int	LuaFann121_UpdateWeightsQuickprop(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(fann*, pAnn, 1)
	unsigned int dataLength = (unsigned int)lua_tonumber(L, 2);

	fann_update_weights_quickprop(pAnn, dataLength);

	return true;
}

int	LuaFann121_UpdateWeightsIrpropm(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(fann*, pAnn, 1)
	unsigned int dataLength = (unsigned int)lua_tonumber(L, 2);

	fann_update_weights_irpropm(pAnn, dataLength);

	return true;
}

int	LuaFann121_UpdateWeightsBatch(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(fann*, pAnn, 1)
	unsigned int dataLength = (unsigned int)lua_tonumber(L, 2);

	fann_update_weights_batch(pAnn, dataLength);	

	return true;
}

int	LuaFann121_Train(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)

	POP_ARGUMENT(fann*, pAnn, 1)
	POP_ARGUMENT(IDataFactory*, piInputData, 2);
	POP_ARGUMENT(IDataFactory*, piOutputData, 3);	

	fann_train(pAnn, piInputData->GetData(), piOutputData->GetData());

	return true;
}

int	LuaFann121_IsSlopesUpdateRequired(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1)

	if(pAnn->prev_train_slopes == NULL)
		lua_pushboolean(L, true);
	else
		lua_pushboolean(L, false);		

	return true;
}

int	LuaFann121_UpdateSlopesBatch(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1)

	fann_update_slopes_batch(pAnn);

	return true;
}
