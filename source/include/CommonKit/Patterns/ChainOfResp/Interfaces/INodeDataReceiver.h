#ifndef IDATARECEIVER_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define IDATARECEIVER_H__CHAINOFRESP__COMMONKIT__INCLUDED_

template 
<
	class T
>
interface INodeDataReceiver : public MinCOM::ICommon
{
	virtual result			SetInputData(T data) = 0;
};

#endif // !IDATARECEIVER_H__CHAINOFRESP__COMMONKIT__INCLUDED_
