#ifndef BAND_H__WORKSPACE__INCLUDED_
#define BAND_H__WORKSPACE__INCLUDED_

namespace Workspace
{

class Band
{
public:
	Band(IPGMBitmap* piBandBitmap, const StringA& fileName, const StringA& bandName);
	virtual ~Band();

	IPGMBitmap*				GetBitmap();
	StringA					GetFileName();	
	StringA					GetBandName();

private:
	IPGMBitmap*				piBandBitmap_;
	StringA					fileName_;
	StringA					bandName_;
};

typedef IContainer<Band*>									IBandsContainer;
typedef IEnumerator<Band*>									IBandsEnumerator;
typedef CContainer<Band*, VectorStorage, Copy, NoRefs>		BandsList;

}

#endif // !BAND_H__WORKSPACE__INCLUDED_
