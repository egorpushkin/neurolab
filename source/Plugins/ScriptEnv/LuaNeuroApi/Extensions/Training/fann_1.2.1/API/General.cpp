#include "StdAfx.h"
#include "General.h"

#include "..\..\..\..\ApiMacro.h"

#include "../Engine/fann.h"

int LuaFann121_CreateArray(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)

	float connectionRate = (float)lua_tonumber(L, 1);
	float learningRate = (float)lua_tonumber(L, 2);
	POP_ARGUMENT(IDataFactory*, piLayersFactory, 3)

	unsigned int length = piLayersFactory->GetDataLength();
	unsigned int* layers = new unsigned int[length]; 
	for (unsigned int i = 0;i < length;i++)
	{
		layers[i] = (unsigned int)piLayersFactory->GetItemData(i);
		if (layers[i] <= 0)
		{
			delete layers;
			return false;
		}
	}

	fann* pAnn = fann_create_array(connectionRate, learningRate, length, layers);

	delete[] layers;

	PUSH_ARGUMENT(fann*, pAnn, -2);

	return true;
}

int LuaFann121_Destroy(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1);

	fann_destroy(pAnn);

    return true;
}

int LuaFann121_Run(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(fann*, pAnn, 1);
	POP_ARGUMENT(IDataFactory*, piInputData, 2);

	fann_run(pAnn, piInputData->GetData());

	return true;
}

int LuaFann121_GetOutputData(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(fann*, pAnn, 1);
	POP_ARGUMENT(IDataFactory*, piDataFactory, 2);

	if (piDataFactory->GetDataLength() != pAnn->num_output)
		piDataFactory->CreateFactory(pAnn->num_output);

	memcpy(
		piDataFactory->GetData(), 
		pAnn->output, 
		sizeof(float) * pAnn->num_output);

	return true;
}

int LuaFann121_GetOutputsCount(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1);	

	unsigned int count = pAnn->num_output;

    lua_pushnumber(L, count);

	return true;
}
