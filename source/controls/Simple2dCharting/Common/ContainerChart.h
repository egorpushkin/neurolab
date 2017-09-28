#ifndef CONTAINERCHART_H__S2DCHARTING__INCLUDED_
#define CONTAINERCHART_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	template
	<
		class T
	>
	class ContainerChart : public BasicChart
	{
	public:

		class ChartLocker_
		{
		public:

			ChartLocker_(nvwa::fast_mutex* pMutex);
			~ChartLocker_();

		private:
			nvwa::fast_mutex* pMutex_;
		};

		typedef Loki::StrongPtr< ChartLocker_ > ChartLockerPtr_;

		typedef std::vector< T > Container_;
		typedef typename std::vector< T >::iterator ContainerIter_;
		typedef typename std::vector< T >::const_iterator ContainerCIter_;

		ContainerChart();
		virtual ~ContainerChart();

		// Public interface
		virtual void Lock();
		virtual void Unlock();
		virtual ChartLockerPtr_ GetLocker();

		virtual void Insert(T val);

		virtual ContainerIter_ begin();
		virtual ContainerCIter_ begin() const;

		virtual ContainerIter_ end();
		virtual ContainerCIter_ end() const;

		virtual Container_& GetContainer();
		virtual const Container_& GetContainer() const;

		virtual BasicChartPtr Clone();

	private:

        Container_ container_;

		nvwa::fast_mutex mutex_;

	}; // ContainerChart

} // Simple2dCharting

#endif // !CONTAINERCHART_H__S2DCHARTING__INCLUDED_
