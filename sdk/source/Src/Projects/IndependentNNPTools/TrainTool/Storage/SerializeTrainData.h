#ifndef SERIALIZETRAINDATA_H__TRAINTOOL__INCLUDED_
#define SERIALIZETRAINDATA_H__TRAINTOOL__INCLUDED_

class TrainDataSerializer
{
public:
	static result LoadData(const StringA& fileName, IDataFile** ppTargetFile)
	{
		*ppTargetFile = NULL;

		FILEDev fileDev;
		result resultCode = fileDev.Open(fileName.c_str(), ModeRead);
		if (FAILED(resultCode))
			return resultCode;

		uint samplesCount = 0;
		uint inputsCount = 0;
		uint outputsCount = 0;

		fscanf(fileDev, "%d", &samplesCount);
		fscanf(fileDev, "%d", &inputsCount);
		fscanf(fileDev, "%d", &outputsCount);

		*ppTargetFile = CConstructTool<CDataFile, IDataFile>::ConstructObject(IID_IDataFile);

		IDataFactory* piInputFactory = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
		piInputFactory->CreateFactory(inputsCount);

		IDataFactory* piOutputFactory = CConstructTool<CDataFactory, IDataFactory>::ConstructObject(IID_IDataFactory);
		piOutputFactory->CreateFactory(outputsCount);

		(*ppTargetFile)->CreateNewFile(inputsCount, outputsCount);
		for (uint i = 0;i < samplesCount;i++)
		{
			for ( uint j = 0 ; j < inputsCount ; j++)
			{
				float sampleItem = 0.0f;
                fscanf(fileDev, "%f", &sampleItem);
				piInputFactory->SetItemData(j, sampleItem);
			}

			for ( uint j = 0 ; j < outputsCount ; j++)
			{
				float sampleItem = 0.0f;
				fscanf(fileDev, "%f", &sampleItem);
				piOutputFactory->SetItemData(j, sampleItem);
			}

			(*ppTargetFile)->AddInputSymbol(piInputFactory);
			(*ppTargetFile)->AddOutputSymbol(piOutputFactory);
		}
	
		piInputFactory->Release();
		piOutputFactory->Release();

		return S_OK;
	}

};

#endif // !SERIALIZETRAINDATA_H__TRAINTOOL__INCLUDED_
