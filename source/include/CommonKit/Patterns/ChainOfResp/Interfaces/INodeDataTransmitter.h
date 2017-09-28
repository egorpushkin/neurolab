#ifndef IDATATRANSMITTER_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define IDATATRANSMITTER_H__CHAINOFRESP__COMMONKIT__INCLUDED_

template 
<
	class U
>
interface INodeDataTransmitter : public MinCOM::ICommon
{
	virtual result			GetOutputData(U& data) const = 0;
};

#endif // !IDATATRANSMITTER_H__CHAINOFRESP__COMMONKIT__INCLUDED_
