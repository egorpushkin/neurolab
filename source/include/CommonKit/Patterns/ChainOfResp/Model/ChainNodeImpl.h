#ifndef CHAINNODEIMPL_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define CHAINNODEIMPL_H__CHAINOFRESP__COMMONKIT__INCLUDED_

template
<
	class T,
	class U
>
class ChainNodeImpl
	: public MinCOM::CommonImpl< INodeDataReceiver<T> >
	, public MinCOM::CommonImpl< IChainNode >
	, public MinCOM::CommonImpl< INodeDataTransmitter<U> >
{
	typedef T InputNodeType;
	typedef U OutputNodeType;

public:

	ChainNodeImpl()
		: piPrevNode_(NULL)
		, piNextNode_(NULL)
		, inputData_()
		, outputData_()
	{
	}

	virtual ~ChainNodeImpl()
	{
	}	

	// ChainNodeImpl template method
	virtual result DoProcessNode() = 0;

	// INodeDataReceiver<T> implementations section
	virtual result SetInputData(InputNodeType data)
	{
		inputData_ = data;
		return S_OK;
	}

	// IChainNode implementations section
	virtual result SetPrevNode(const IChainNodePtr& piPrevNode)
	{
		piPrevNode_ = GetImpl(piPrevNode);
		return S_OK;
	}

	virtual result SetNextNode(const IChainNodePtr& piNextNode)
	{
		piNextNode_ = GetImpl(piNextNode);
		return S_OK;
	}
	
	virtual result ProcessNode()
	{
		DoProcessNode();

		if (piNextNode_)
		{
			MinCOM::ComPtr< INodeDataReceiver<OutputNodeType> > 
				piNodeReceiver(piNextNode_, IID_INodeDataReceiver);
			piNodeReceiver->SetInputData(outputData_);
		}

		return S_OK;
	}

	// INodeDataTransmitter<U> implementations section
	virtual result GetOutputData(OutputNodeType& data) const
	{
		data = outputData_;			 
		return S_OK;
	}

	// ICommon implementations section
	virtual result QueryInterface(REFIID iid, void** ppObject)
	{
		if (iid == MinCOM::IID_ICommon)
			*ppObject = MinCOM::CommonImpl< IChainNode >::GetCommon(); 
			
		else if (iid == IID_INodeDataReceiver)
			*ppObject = static_cast< INodeDataReceiver<InputNodeType>* >(this);

		else if (iid == IID_IChainNode)
			*ppObject = static_cast< IChainNode* >(this);

		else if (iid == IID_INodeDataTransmitter)
			*ppObject = static_cast< INodeDataTransmitter<OutputNodeType>* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		MinCOM::CommonImpl< IChainNode >::GetCommon()->AddRef();
		return S_OK;
	}

protected:
	IChainNode* piPrevNode_;
	IChainNode* piNextNode_;

	InputNodeType inputData_;
	OutputNodeType outputData_;

};

#endif // !CHAINNODEIMPL_H__CHAINOFRESP__COMMONKIT__INCLUDED_
