#ifndef IDATATRANSMITTER_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define IDATATRANSMITTER_H__CHAINOFRESP__COMMONKIT__INCLUDED_

template 
<
	class U
>
interface INodeDataTransmitter : public MinCOM::ICommon
{
	virtual result GetOutputData(U& data) const = 0;
};

// {3bcded86-c94f-4db4-8464-4876d170cb91} 
DEFINE_GUID(IID_INodeDataReceiver, 
0x3bcded86, 0xc94f, 0x4db4, 0x84, 0x64, 0x48, 0x76, 0xd1, 0x70, 0xcb, 0x91);

#endif // !IDATATRANSMITTER_H__CHAINOFRESP__COMMONKIT__INCLUDED_
