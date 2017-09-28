#ifndef CMNLAYER_H__BUILDERELEMENTS__INCLUDED_
#define CMNLAYER_H__BUILDERELEMENTS__INCLUDED_

class CCmnLayer 
	: public NetworkImportingKit::ILayerControl
	, public IStorageController
{
public:
	CCmnLayer();
	virtual ~CCmnLayer();

protected:
	// Custom tools
	void					FlowLayerData();
	void					ProcessLayer();

	// Custom allocation tools
	virtual void			CustomCreateWeights(uint inputsCount, uint layerDimension);
	virtual void			CustomReleaseWeights();

	// IStorageController declarations section
	virtual result			Serialize(FILEDev& fileDev, bool loading);

	// ILayerControl implementations section
	virtual void			SetInputData(const IDataFactory* piData);
	virtual void			SetOutputData(const IDataFactory* piData);

	virtual void			GetInputData(IDataFactory* piData) const;
	virtual void			GetOutputData(IDataFactory* piData) const;

	virtual void			CreateWeights(uint inputsCount, uint layerDimension);
	virtual void			ReleaseWeights();

	virtual bool			ModifyWeights();
	virtual void			ResetWeights(float value);

	virtual uint			GetDimension() const;
	virtual uint			GetInputsCount() const;

	virtual float			GetWeight(uint input, uint neuron) const;
	virtual void			SetWeight(uint input, uint neuron, float weightValue);

	virtual void			SetDelta(uint neuron, float deltaValue);
	virtual float			GetDelta(uint neuron) const;

protected:
	IDataFactory*			piInputData_;
	IDataFactory*			piOutputData_;

	uint					layerDimension_;
	uint					inputsCount_;

	vector<IDataFactory*>	layerWeights_;
	IDataFactory*			piDeltas_;
};

#endif // !CMNLAYER_H__BUILDERELEMENTS__INCLUDED_
