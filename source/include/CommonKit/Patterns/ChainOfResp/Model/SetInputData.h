#ifndef SETINPUTDATA_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define SETINPUTDATA_H__CHAINOFRESP__COMMONKIT__INCLUDED_

template 
< 
	class T 
>
result SetInputData(const IChainProcessorPtr& piChainProcessor, T data)
{
	IChainNodePtr piFirstNode = NULL;
	result r = piChainProcessor->GetFirstNode(&piFirstNode);
	if (FAILED(r))
		return r;

	MinCOM::ComPtr< INodeDataReceiver<T> > 
		piNodeReceiver(piFirstNode, ChainOfResp::IID_INodeDataReceiver);
	
	return piNodeReceiver->SetInputData(data);
}

#endif // !SETINPUTDATA_H__CHAINOFRESP__COMMONKIT__INCLUDED_
