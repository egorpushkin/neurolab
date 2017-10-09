#ifndef ICHAINNODE_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define ICHAINNODE_H__CHAINOFRESP__COMMONKIT__INCLUDED_

interface IChainNode;

typedef MinCOM::ComPtr< IChainNode > IChainNodePtr;

interface IChainNode : public MinCOM::ICommon
{
	virtual result			SetPrevNode(const IChainNodePtr& piPrevNode) = 0;
	virtual result			SetNextNode(const IChainNodePtr& piNextNode) = 0;

	virtual result			ProcessNode() = 0;
};

#endif // !ICHAINNODE_H__CHAINOFRESP__COMMONKIT__INCLUDED_
