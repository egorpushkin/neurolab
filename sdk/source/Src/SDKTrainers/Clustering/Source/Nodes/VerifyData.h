#ifndef VERIFYDATA_H__TRAINER__INCLUDED_
#define VERIFYDATA_H__TRAINER__INCLUDED_

namespace Trainer
{

	class VerifyData
		: public TrainerChainImpl
	{

		VerifyData(const VerifyData&);
		VerifyData& operator =(const VerifyData&);

	public:
		VerifyData();
		virtual ~VerifyData();

	protected:
		// ChainNodeImpl template method
		virtual result DoProcessNode();

	};

} // namespace Trainer

#endif // !VERIFYDATA_H__TRAINER__INCLUDED_
