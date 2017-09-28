#include "StdAfx.h"
#include "General.h"

#include "..\..\..\..\ApiMacro.h"
#include "..\..\..\..\GlobalStorage.h"

#include "../Engine/fann.h"

int LuaFann121_FannTrainDataFromDataFile(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(IDataFile*, pDataFile, 1)

	fann_train_data* pTrainData = new fann_train_data;

	pTrainData->errno_f = 0;
	pTrainData->error_log = NULL;
	pTrainData->errstr = NULL;

	pTrainData->num_input = pDataFile->GetInputSymbolLength();
	pTrainData->num_output = pDataFile->GetOutputSymbolLength();
	pTrainData->num_data = pDataFile->GetInputSymbolsCount();

	pTrainData->input = new fann_type*[pTrainData->num_data];
	for (unsigned int i = 0; i < pTrainData->num_data; ++i)
	{
		pTrainData->input[i] = new fann_type[pTrainData->num_input];
        memcpy(pTrainData->input[i], pDataFile->GetInputSymbol(i)->GetData(), pTrainData->num_input * sizeof(float));
	}

	pTrainData->output = new fann_type*[pTrainData->num_data];
	for (unsigned int i = 0; i < pTrainData->num_data; ++i)
	{
		pTrainData->output[i] = new fann_type[pTrainData->num_output];
		memcpy(pTrainData->output[i], pDataFile->GetOutputSymbol(i)->GetData(), pTrainData->num_output * sizeof(float));
	}

	PUSH_ARGUMENT(fann_train_data*, pTrainData, -2)

	return true;
}

int LuaFann121_ReleaseFannTrainData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann_train_data*, pTrainData, 1)

	if (pTrainData->input)
	{
		for (unsigned int i = 0; i < pTrainData->num_data; ++i)
			delete[] pTrainData->input[i];

		delete[] pTrainData->input;		
	}

	if (pTrainData->output)
	{
		for (unsigned int i = 0; i < pTrainData->num_data; ++i)
			delete[] pTrainData->output[i];

		delete[] pTrainData->output;		
	}

	delete pTrainData;

    return true;
}