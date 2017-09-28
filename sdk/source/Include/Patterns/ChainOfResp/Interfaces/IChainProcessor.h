#ifndef ICHAINPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define ICHAINPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_

interface IChainProcessor : public MinCOM::ICommon
{
	virtual result AddNode(const IChainNodePtr& piNode) = 0;
	
	virtual result ProcessChain() const = 0;

	virtual result GetFirstNode(IChainNodePtr* ppiNode) const = 0;
	virtual result GetLastNode(IChainNodePtr* ppiNode) const = 0;	
};

typedef MinCOM::ComPtr< IChainProcessor > IChainProcessorPtr;

// {2d00a907-d09f-46c2-843d-93f9cdf82f1c} 
DEFINE_GUID(IID_IChainProcessor, 
0x2d00a907, 0xd09f, 0x46c2, 0x84, 0x3d, 0x93, 0xf9, 0xcd, 0xf8, 0x2f, 0x1c);

#endif // !ICHAINPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_
