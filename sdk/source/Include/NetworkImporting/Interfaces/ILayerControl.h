//	This code is a part of 'Network Importing SDK' product.
//	Copyright (C) Scientific Software
//	All rights reserved.

//	File name: ILayerControl.h
//	Description: The ILayerControl declaration.

#ifndef ILAYERCONTROL_H__NETWORKIMPORTING__INCLUDED_
#define ILAYERCONTROL_H__NETWORKIMPORTING__INCLUDED_

// ILayerControl declaration
interface ILayerControl : public ICommon
{
	// Layer data initialization
	virtual void			SetInputData(const IDataFactory* piData) = 0;
	virtual void			SetOutputData(const IDataFactory* piData) = 0;

	virtual void			GetInputData(IDataFactory* piData) const = 0;
	virtual void			GetOutputData(IDataFactory* piData) const = 0;

	// Layer state routines
	virtual void			CreateWeights(uint inputsCount, uint layerDimension) = 0;
	virtual void			ReleaseWeights() = 0;

	virtual bool			ModifyWeights() = 0;
	virtual void			ResetWeights(float value) = 0;

	// Layer characteristics
	virtual uint			GetDimension() const = 0;
	virtual uint			GetInputsCount() const = 0;

	// Weights and deltas manipulation
	virtual float			GetWeight(uint input, uint neuron) const = 0;
	virtual void			SetWeight(uint input, uint neuron, float weightValue) = 0;

	virtual void			SetDelta(uint neuron, float deltaValue) = 0;
	virtual float			GetDelta(uint neuron) const = 0;
};

typedef ComPtr<	ILayerControl > ILayerControlPtr;
typedef const ILayerControlPtr& ILayerControlRef;

#endif // !ILAYERCONTROL_H__NETWORKIMPORTING__INCLUDED_
