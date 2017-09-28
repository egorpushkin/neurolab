#ifndef EXECUTION_H__TRAINERSMANAGER__INCLUDED_
#define EXECUTION_H__TRAINERSMANAGER__INCLUDED_

/**
* Synchronous and asynchronous execution support. 
* Widely used in IGeneralProcessor2 (which has not been defined yet in 1.0.1). 
*
* @version 1.0.1
*/

enum ExecutionType
{
	DefaultExecutio				= 0,
	Synchronous					= 1, 
	Asynchronous				= 2
};

#endif // !EXECUTION_H__TRAINERSMANAGER__INCLUDED_
