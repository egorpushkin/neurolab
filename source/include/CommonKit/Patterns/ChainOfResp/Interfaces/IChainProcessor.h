#ifndef ICHAINPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define ICHAINPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_

interface IChainProcessor : public MinCOM::ICommon
{
	virtual result			AddNode(const IChainNodePtr& piNode) = 0;
	
	virtual result			ProcessChain() const = 0;

	virtual result			GetFirstNode(IChainNodePtr* ppiNode) const = 0;
	virtual result			GetLastNode(IChainNodePtr* ppiNode) const = 0;	
};

typedef MinCOM::ComPtr< IChainProcessor > IChainProcessorPtr;

#endif // !ICHAINPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_
