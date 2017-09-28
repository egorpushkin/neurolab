#include "../../PrecompiledHeader.h"

#include "Band.h"

namespace Workspace
{

Band::Band(IPGMBitmap* piBandBitmap, const StringA& fileName, const StringA& bandName)
	: piBandBitmap_(piBandBitmap)
	, fileName_(fileName)
	, bandName_(bandName)
{
	if (piBandBitmap_)
		piBandBitmap_->AddRef();
}

Band::~Band()
{
	if (piBandBitmap_)
		piBandBitmap_->Release();
}

IPGMBitmap* Band::GetBitmap()
{
	if (piBandBitmap_)
		piBandBitmap_->AddRef();

	return piBandBitmap_;
}

StringA Band::GetFileName()
{
	return fileName_;
}

StringA Band::GetBandName()
{
	return bandName_;
}

}
