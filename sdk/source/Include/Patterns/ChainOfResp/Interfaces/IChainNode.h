#ifndef ICHAINNODE_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define ICHAINNODE_H__CHAINOFRESP__COMMONKIT__INCLUDED_

interface IChainNode;
typedef MinCOM::ComPtr< IChainNode > IChainNodePtr;

interface IChainNode : public MinCOM::ICommon
{
	virtual result SetPrevNode(const IChainNodePtr& piPrevNode) = 0;
	virtual result SetNextNode(const IChainNodePtr& piNextNode) = 0;

	virtual result ProcessNode() = 0;
};

// {ce1569fb-6072-4f6b-8a43-718c82b521dc} 
DEFINE_GUID(IID_IChainNode, 
0xce1569fb, 0x6072, 0x4f6b, 0x8a, 0x43, 0x71, 0x8c, 0x82, 0xb5, 0x21, 0xdc);

#endif // !ICHAINNODE_H__CHAINOFRESP__COMMONKIT__INCLUDED_
