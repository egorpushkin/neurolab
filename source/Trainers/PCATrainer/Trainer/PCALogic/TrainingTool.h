#pragma once

#include "DuplicateInputData.h"
#include "NormalizeData.h"
#include "CovarianceTool.h"

#include "../../MathTools/NewMat11/Source/newmat.h"
#include "../../MathTools/NewMat11/Source/newmatap.h"

class CTrainingTool
{
public:
	CTrainingTool()
		: iProcessed(0)
	{
	}

	void ProcessMethod(
		IDataFile*			pDataFile,
		ILayerControl*		pLayerControl,
		ILogProvider*		pLogProvider,
		sPCASettings*		pSettings)
	{

		AddLogMessage(pLogProvider, CString(_T("Starting generation...")));
		
		// Creating copy of input data		
		AddLogMessage(pLogProvider, CString(_T("Creating copy of input data...")));

		CDataFileDuplicator mCurDataFile;
		mCurDataFile.Duplicate(pDataFile);

		IDataFile* pCurDataFile = NULL;
		mCurDataFile.QueryInterface(IDD_IDataFile, (void**)&pCurDataFile);

		AddLogMessage(pLogProvider, CString(_T("Creating copy of input data. Done.")));

		// Normalizing data
		AddLogMessage(pLogProvider, CString(_T("Normalizing input data...")));

		CNormalizeData::NormalizeData(pDataFile, pCurDataFile);

		AddLogMessage(pLogProvider, CString(_T("Normalizing input data. Done.")));

		// Calculating the covariance matrix
		AddLogMessage(pLogProvider, CString(_T("Calculating the covariance matrix...")));

		CDataFile mCovarDataFile;
		mCovarDataFile.CreateNewFile(pCurDataFile->GetInputSymbolLength(), 1);
		
		for (int i = 0;i < pCurDataFile->GetInputSymbolLength();i++)
			mCovarDataFile.AddInputSymbol(0.0f);

		IDataFile* pCovarDataFile = NULL;
		mCovarDataFile.QueryInterface(IDD_IDataFile, (void**)&pCovarDataFile);

		CCovarianceTool::CaclulateCovariance(pCurDataFile, pCovarDataFile);

		AddLogMessage(pLogProvider, CString(_T("Calculating the covariance matrix. Done.")));
		
		// Calculating egenvalues and egenvectors 
		AddLogMessage(pLogProvider, CString(_T("Calculating eigenvalues and eigenvectors...")));

		SymmetricMatrix symmmatrCovar(pCurDataFile->GetInputSymbolLength());

		for (int i = 0;i < pCovarDataFile->GetInputSymbolLength();i++)
			for (int j = 0;j < pCovarDataFile->GetInputSymbolLength();j++)			
				symmmatrCovar(i + 1, j + 1) = pCovarDataFile->GetInputSymbol(i)->GetItemData(j);

		DiagonalMatrix diagmatrEgenval(pCovarDataFile->GetInputSymbolLength());
		Matrix matrEgenvect(pCovarDataFile->GetInputSymbolLength(), pCovarDataFile->GetInputSymbolLength());

        //Jacobi(symmmatrCovar, diagmatrEgenval, matrEgenvect);
		eigenvalues(symmmatrCovar, diagmatrEgenval, matrEgenvect);

		AddLogMessage(pLogProvider, CString(_T("Calculating eigenvalues and eigenvectors. Done.")));

		// Fill layer weights with found egenvectors
		AddLogMessage(pLogProvider, CString(_T("Returning data...")));

		for (int i = 0;i < pCovarDataFile->GetInputSymbolLength();i++)
			for (int j = 0;j < pSettings->iFeaturesCount;j++)
			{
				int iReversedInd = pCovarDataFile->GetInputSymbolLength() - j - 1;

				pLayerControl->SetWeight(i, j, 
					matrEgenvect(i + 1, iReversedInd + 1));
			}

		AddLogMessage(pLogProvider, CString(_T("Returning data. Done.")));

		AddLogMessage(pLogProvider, CString(_T("Features generation. Done.")));
	}

	void AddLogMessage(
		ILogProvider*		pLogProvider,
		CString&			csMessage)
	{
		pLogProvider->AddLogMessage(CString("N"), 
			csMessage, 
			CString("PCA Fetures Generation"));
	}

	int GetPercentage()
	{
		return iProcessed;
	}

private:
	int				iProcessed;
};