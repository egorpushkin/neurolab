#ifndef GETOUTPUTDATA_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define GETOUTPUTDATA_H__CHAINOFRESP__COMMONKIT__INCLUDED_

template 
< 
	class U 
>
result GetOutputData(const IChainProcessorPtr& piChainProcessor, U& data)
{
	IChainNodePtr piLastNode = NULL;
	result r = piChainProcessor->GetLastNode(&piLastNode);
	if (FAILED(r))
		return r;

	MinCOM::ComPtr< INodeDataTransmitter<U> > 
		piNodeTransmitter(piLastNode, ChainOfResp::IID_INodeDataTransmitter);

	return piNodeTransmitter->GetOutputData(data);
}

#endif // !GETOUTPUTDATA_H__CHAINOFRESP__COMMONKIT__INCLUDED_
