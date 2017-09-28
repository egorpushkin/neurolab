#include "TrainerMain.h"

#include "ArgumentsTool.h"

namespace Trainer
{

	MinCOM::CommonVariant GetArgument(TrMngKit::ITrainerRef trainer, const StringA& name)
	{
		MinCOM::CommonVariant value;

		TrMngKit::IPropertiesPtr properties(trainer, TrMngKit::IID_IProperties);

		result r = properties->GetArgument(name, value);
		if ( FAILED(r) )
		{
			if ( name == StringA("WeightsInit") )
			{
				value.vt_ = CE_UINT;
				value.uintVal_ = 3;
			} 
			else if ( name == StringA("TrainingMethod") )
			{
				value.vt_ = CE_UINT;
				value.uintVal_ = 0;
			}
			else if ( name == StringA("LearningRate") )
			{
				value.vt_ = CE_R4;
				value.fltVal_ = 0.7f;
			}
			else if ( name == StringA("MaxMSE") )
			{
				value.vt_ = CE_R4;
				value.fltVal_ = 0.01f;
			}
			else if ( name == StringA("MaxEpochs") )
			{
				value.vt_ = CE_UINT;
				value.uintVal_ = 10000;
			}
			else if ( name == StringA("EpochsBetweenReport") )
			{
				value.vt_ = CE_UINT;
				value.uintVal_ = 10;
			}
			else if ( name == StringA("HiddenActivation") )
			{
				value.vt_ = CE_UINT;
				value.uintVal_ = 5;
			}
			else if ( name == StringA("OutputActivation") )
			{
				value.vt_ = CE_UINT;
				value.uintVal_ = 3;
			}
		}

		return value;
	}

}
