#ifndef IDATARECEIVER_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define IDATARECEIVER_H__CHAINOFRESP__COMMONKIT__INCLUDED_

template 
<
	class T
>
interface INodeDataReceiver : public MinCOM::ICommon
{
	virtual result SetInputData(T data) = 0;
};

// {94952b32-d5ea-40ef-9c9b-07069913eb66} 
DEFINE_GUID(IID_INodeDataTransmitter, 
0x94952b32, 0xd5ea, 0x40ef, 0x9c, 0x9b, 0x07, 0x06, 0x99, 0x13, 0xeb, 0x66);

#endif // !IDATARECEIVER_H__CHAINOFRESP__COMMONKIT__INCLUDED_
