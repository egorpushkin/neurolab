#pragma once

#include "CmnTrainers.h"

#define DLL_FUNC_DECLARE extern "C" __declspec(dllexport)

DLL_FUNC_DECLARE ITrainer*				CreateTrainerInstance();
DLL_FUNC_DECLARE void					ReleaseTrainerInstance(ITrainer* pTrainer);