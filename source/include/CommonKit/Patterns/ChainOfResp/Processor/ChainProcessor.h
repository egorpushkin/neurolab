#ifndef CHAINPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define CHAINPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_

class ChainProcessor
	: public MinCOM::CommonImpl< IChainProcessor >
{
public:
	ChainProcessor()
		: nodes_()
	{
	}

	virtual ~ChainProcessor() {}

	// IChainProcessor implementations section
	virtual result AddNode(const IChainNodePtr& piNode)
	{
		if (nodes_.size() > 0)
		{
			const IChainNodePtr& piPrevNode = *(--nodes_.end());			

			piNode->SetPrevNode(piPrevNode);
			piPrevNode->SetNextNode(piNode);
		}	

		nodes_.push_back(piNode);
		return S_OK;
	}

	virtual result ProcessChain() const 
	{
		for (NodesContainer::const_iterator it = nodes_.begin();it != nodes_.end();it++)
		{
			result r = (*it)->ProcessNode();
			if (FAILED(r))
				return r;
		}

		return S_OK;
	}

	virtual result GetFirstNode(MinCOM::ComPtr< ChainOfResp::IChainNode >* ppiNode) const
	{
		if (nodes_.size() == 0)
			return E_FAIL;

		(*ppiNode) = *(nodes_.begin());		
		return S_OK;
	}

	virtual result GetLastNode(MinCOM::ComPtr< IChainNode >* ppiNode) const 
	{
		if (nodes_.size() == 0)
			return E_FAIL;

		(*ppiNode) = *(--nodes_.end());		
		return S_OK;
	}

	// ICommon implementations section
	virtual result QueryInterface(REFIID iid, void** ppObject)
	{
		if (iid == MinCOM::IID_ICommon)
			*ppObject = MinCOM::CommonImpl< IChainProcessor >::GetCommon(); 

		else if (iid == IID_IChainProcessor)
			*ppObject = static_cast< IChainProcessor* >(this);

		else
		{
			*ppObject = NULL;
			return E_NOINTERFACE;
		}

		MinCOM::CommonImpl< IChainProcessor >::GetCommon()->AddRef();
		return S_OK;
	}

private:
	typedef std::vector< const IChainNodePtr > NodesContainer;
	NodesContainer nodes_;

};

#endif // !CHAINPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_
