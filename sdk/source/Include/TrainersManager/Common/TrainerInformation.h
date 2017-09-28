#ifndef TRAINERINFORMATION_H__TRAINERSMANAGER__INCLUDED_
#define TRAINERINFORMATION_H__TRAINERSMANAGER__INCLUDED_

// Trainer version information 

namespace Private
{

	/**
	* SIZE_INFO structure. Contains structure size information.
	*
	* @version 1.0.1
	*/
	typedef struct _SIZE_INFO
	{

		_SIZE_INFO(uint size) 
			: size_(size)	{}

		_SIZE_INFO(const _SIZE_INFO& arg) 
			: size_(arg.size_) {}
		_SIZE_INFO& operator =(const _SIZE_INFO&) {}   

		// Structure size. Used to check versions' correspondence.
		const uint				size_;

	} SIZE_INFO;

}

/**
* VERSION structure. Contains version information.
*
* @version 1.0.1
*/
typedef struct _VERSION
	: public Private::SIZE_INFO
{

	_VERSION()
		: Private::SIZE_INFO(sizeof(_VERSION)) {}

	// High version number
	uint					verHi_;
	// Low version number
	uint					verLow_;
	// Build number
	uint					verBuild_;
	// String version presentation
	StringA					version_;

} VERSION, *PVERSION;

typedef const VERSION& REFVERSION;

/**
* TRAINER_INFO structure. Contains trainer general information. 
*
* @version 1.0.1
*/
typedef struct _TRAINER_INFO
	: public Private::SIZE_INFO
{

	_TRAINER_INFO()
		: Private::SIZE_INFO(sizeof(_TRAINER_INFO))	{}

	// Trainer library system (internal) name
	StringA					name_;
	// Trainer library title
	StringA					title_;
	// Trainer library unique identifier
	CLSID					clsid_;
	// Trainer version information
	VERSION					version_;

} TRAINER_INFO, *PTRAINER_INFO;

static const uint TRINFO_SIZE_V1 = sizeof(TRAINER_INFO);
static const uint VERINFO_SIZE_V1 = sizeof(VERSION);

__inline bool operator < (REFVERSION left, REFVERSION right)
{
	if (left.verHi_ < right.verHi_)
		return true;

	if ((left.verHi_ == right.verHi_) && 
		(left.verLow_ < right.verLow_))
		return true;

	if ((left.verHi_ == right.verHi_) && 
		(left.verLow_ == right.verLow_) && 
		(left.verBuild_ < right.verBuild_))
		return true;

	return false;
}

__inline bool operator >= (REFVERSION left, REFVERSION right)
{
	return !operator < (left, right);
}

#endif // !TRAINERINFORMATION_H__TRAINERSMANAGER__INCLUDED_
