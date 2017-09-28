#ifndef ADDNODE_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define ADDNODE_H__CHAINOFRESP__COMMONKIT__INCLUDED_

template 
< 
	class T 
>
result AddNode(const IChainProcessorPtr& piChainProcessor, T* pNode)
{
	IChainNodeQIPtr piChainNode(pNode, IID_IChainNode);
	return piChainProcessor->AddNode(piChainNode);
}

#endif // !ADDNODE_H__CHAINOFRESP__COMMONKIT__INCLUDED_
