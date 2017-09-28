
namespace Simple2dCharting
{

	// ContainerChart::ChartLocker_
	template< class T >
	ContainerChart< T >::ChartLocker_::ChartLocker_(nvwa::fast_mutex* pMutex)
		: pMutex_(pMutex)
	{
		if ( !pMutex_ )
			throw std::exception("Wrong ChartLocker_ instance initialization.");

		pMutex_->lock();
	}

	template< class T >
	ContainerChart< T >::ChartLocker_::~ChartLocker_()
	{
		pMutex_->unlock();
	}

	// ContainerChart
	template< class T >
	ContainerChart< T >::ContainerChart()
		: container_()
	{
	}

	template< class T >
	ContainerChart< T >::~ContainerChart()
	{
	}

	// Public interface
	template< class T >
	void ContainerChart< T >::Lock()
	{
		mutex_.lock();
	}

	template< class T >
	void ContainerChart< T >::Unlock()
	{
		mutex_.unlock();
	}

	template< class T >
	typename ContainerChart< T >::ChartLockerPtr_ ContainerChart< T >::GetLocker()
	{
		return ChartLockerPtr_(
			new ChartLocker_(&mutex_)
		);
	}

	template< class T >
	void ContainerChart< T >::Insert(T val)
	{
		nvwa::fast_mutex_autolock locker(mutex_);

		container_.push_back(val);
	}

	template< class T >
	typename ContainerChart< T >::ContainerIter_ ContainerChart< T >::begin()
	{
		nvwa::fast_mutex_autolock locker(mutex_);

		return container_.begin();
	}

	template< class T >
	typename ContainerChart< T >::ContainerCIter_ ContainerChart< T >::begin() const
	{
		return container_.begin();
	}

	template< class T >
	typename ContainerChart< T >::ContainerIter_ ContainerChart< T >::end()
	{
		nvwa::fast_mutex_autolock locker(mutex_);

		return container_.end();
	}

	template< class T >
	typename ContainerChart< T >::ContainerCIter_ ContainerChart< T >::end() const
	{
		return container_.end();
	}

	template< class T >
	typename ContainerChart< T >::Container_& ContainerChart< T >::GetContainer()
	{
		return container_;
	}

	template< class T >
	const typename ContainerChart< T >::Container_& ContainerChart< T >::GetContainer() const
	{
		return container_;
	}

	template< class T >
	BasicChartPtr ContainerChart< T >::Clone()
	{
		return BasicChartPtr(new ContainerChart< T >);
	}

} // Simple2dCharting
