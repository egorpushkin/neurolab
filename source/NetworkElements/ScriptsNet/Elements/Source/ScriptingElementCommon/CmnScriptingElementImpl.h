#pragma once

#include "CmnScriptingElement.h"

class CCmnScriptingElement : public IScriptingElementControl
{
public:
	CCmnScriptingElement()
		: csProcessElementScript(_T(""))
		, iLayerDimensionSE(0)
		, iInputsCountSE(0)
	{
	}

	virtual bool Serialize(CArchive& ar)
	{
		if (ar.IsLoading())
		{
			int tmLength;
			ar.Read(&tmLength, sizeof(int));
			ar.Read(csProcessElementScript.GetBuffer(16384), tmLength);
			csProcessElementScript.ReleaseBuffer();

			ar.Read(&iLayerDimensionSE, sizeof(int));
			ar.Read(&iInputsCountSE, sizeof(int));
		} else
		{
			int tmLength = csProcessElementScript.GetLength() + 1;
			ar.Write(&tmLength, sizeof(int));
			ar.Write(csProcessElementScript.GetBuffer(), tmLength);

			ar.Write(&iLayerDimensionSE, sizeof(int));
			ar.Write(&iInputsCountSE, sizeof(int));
		}

		return true;
	}

// IScriptingElementControl implementations section
	virtual int GetDimensionSE()
	{
		return iLayerDimensionSE;
	}

	virtual int GetInputsCountSE()
	{
		return iInputsCountSE;
	}
    
	virtual void SetScriptString(CString& ScriptSrting)
	{
		csProcessElementScript = ScriptSrting;
	}

	virtual CString GetScriptString()
	{
		return csProcessElementScript;
	}

protected:
	CString					csProcessElementScript;

	int						iLayerDimensionSE;
	int						iInputsCountSE;
};