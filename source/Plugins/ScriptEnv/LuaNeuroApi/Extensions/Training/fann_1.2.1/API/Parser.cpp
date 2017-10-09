#include "StdAfx.h"
#include "Initialization.h"

#include "..\..\..\..\ApiMacro.h"

#include "../Engine/fann.h"

#include "../Helpers/Parser.h"

int	LuaFann121_GetLayersCount(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(fann*, pAnn, 1);

	if (!pAnn || 
		!pAnn->first_layer || 
		!pAnn->last_layer || 
		pAnn->first_layer == pAnn->last_layer)
		return false;

	unsigned int layers = Parser::GetLayersCount(pAnn);
	lua_pushnumber(L, (double)layers);

	return true;
}

int	LuaFann121_GetLayer(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(fann*, pAnn, 1);
	unsigned int layerIndex = (unsigned int)lua_tonumber(L, 2);

	const fann_layer* pLayer = Parser::GetLayer(pAnn, layerIndex);
	if (!pLayer)
		return false;

	PUSH_ARGUMENT(const fann_layer*, pLayer, -2);

	return true;
}

int	LuaFann121_GetLayerDimension(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(const fann_layer*, pLayer, 1);

	unsigned int neurons = Parser::GetNeuronsCount(pLayer);
	lua_pushnumber(L, (double)neurons);	

	return true;
}

int LuaFann121_GetLayerInputsCount(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(const fann_layer*, pLayer, 1);	

	const fann_neuron* pNeuron = Parser::GetNeuron(pLayer, 0);
	if (!pNeuron)
		return false;

	unsigned int inputs = Parser::GetNeuronInputsCount(pNeuron);
	lua_pushnumber(L, (double)inputs);	    

	return true;
}

int	LuaFann121_GetNeuron(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(const fann_layer*, pLayer, 1);
	unsigned int neuronIndex = (unsigned int)lua_tonumber(L, 2);

	const fann_neuron* pNeuron = Parser::GetNeuron(pLayer, neuronIndex);
	if (!pNeuron)
		return false;

	PUSH_ARGUMENT(const fann_neuron*, pNeuron, -2);

	return true;
}

int	LuaFann121_GetNeuronInputsCount(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(1)

	POP_ARGUMENT(const fann_neuron*, pNeuron, 1);
	
	unsigned int inputs = Parser::GetNeuronInputsCount(pNeuron);
	lua_pushnumber(L, (double)inputs);	  

	return true;
}

int	LuaFann121_GetNeuronWeight(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(2)

	POP_ARGUMENT(const fann_neuron*, pNeuron, 1);
	unsigned int weightIndex = (unsigned int)lua_tonumber(L, 2);

	float weight = Parser::GetNeuronWeight(pNeuron, weightIndex);
	lua_pushnumber(L, (double)weight);	

	return true;
}

int LuaFann121_GetLayerWeight(lua_State *L)
{
	CHECK_ARGUMENTS_COUNT(3)

	POP_ARGUMENT(const fann_layer*, pLayer, 1);
	unsigned int inputIndex = (unsigned int)lua_tonumber(L, 2);
	unsigned int neuronIndex = (unsigned int)lua_tonumber(L, 3);

	const fann_neuron* pNeuron = Parser::GetNeuron(pLayer, neuronIndex);
	if (!pNeuron)
		return false;   

	float weight = Parser::GetNeuronWeight(pNeuron, inputIndex);
	lua_pushnumber(L, (double)weight);	

	return true;
}
