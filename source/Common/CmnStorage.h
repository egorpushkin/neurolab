#pragma once

#include "CmnObjects.h"

interface IStorageController : public IObject
{
	virtual bool			Serialize(CArchive& ar) = 0;
};