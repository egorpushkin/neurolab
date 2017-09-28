#include "StdAfx.h"
#include "ExportSolution.h"

bool CExportSolution::LoadSolution()
{
	return CSolutionSerialize::LoadSolution(this);
}

bool CExportSolution::VerifySolution()
{
	return CSolutionSerialize::VerifySolution(this);
}