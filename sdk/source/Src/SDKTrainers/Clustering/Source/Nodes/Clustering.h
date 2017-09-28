#ifndef CLUSTERING_H__TRAINER__INCLUDED_
#define CLUSTERING_H__TRAINER__INCLUDED_

namespace Trainer
{

	class Clustering
		: public TrainerChainImpl
	{

		Clustering(const Clustering&);
		Clustering& operator =(const Clustering&);

	public:
		Clustering();
		virtual ~Clustering();

	protected:
		// ChainNodeImpl template method
		virtual result DoProcessNode();

	};

} // namespace Trainer

#endif // !CLUSTERING_H__TRAINER__INCLUDED_
