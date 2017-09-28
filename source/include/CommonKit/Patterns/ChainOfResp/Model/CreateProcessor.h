#ifndef CREATEPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_
#define CREATEPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_

IChainProcessorPtr CreateProcessor()
{
	return IChainProcessorQIPtr(new ChainOfResp::ChainProcessor, ChainOfResp::IID_IChainProcessor);
}

#endif // !CREATEPROCESSOR_H__CHAINOFRESP__COMMONKIT__INCLUDED_
