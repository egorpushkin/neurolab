#ifndef ICHARTLOGPROVIDER_H__TRAINERSMANAGER__INCLUDED_
#define ICHARTLOGPROVIDER_H__TRAINERSMANAGER__INCLUDED_

/**
* IChartLogProvider interface. Charting support during training.
*
* @version 1.0.1
*/
interface IChartLogProvider : public ILogProvider
{
	
	/**
	* Adds new chart.
	*
	* @param name Chart unique name.
	* @param title Chart title to be displayed.
	*/
	virtual result AddChart(const StringA& name, const StringA& title) = 0;

	/**
	* Adds new chart point.
	*
	* @param name Chart unique name.
	* @param offset Point offset.
	* @param value Point value.
	*/
	virtual result AddChartItem(const StringA& name, float offset, float value) = 0;

};

#endif // !ICHARTLOGPROVIDER_H__TRAINERSMANAGER__INCLUDED_
