#include "../../PrecompiledHeader.h"

#include "MultispectralImage.h"

namespace Workspace
{

MultispectralImage::MultispectralImage()
	: imageName_("")
	, piBandsContainer_(NULL)
	, width_(0)
	, height_(0)
{
	BandsList* pBandsList = new BandsList;
	piBandsContainer_ = QueryTool<BandsList, IBandsContainer>::QueryInterface(pBandsList, IID_IContainer);
}

MultispectralImage::~MultispectralImage()
{
	CleanUp();
}

// Public Tools
//////////////////////////////////////////////////////////////////////////
void MultispectralImage::SetImageName(const StringA& imageName)
{
	imageName_ = imageName;
}

StringA	MultispectralImage::GetImageName()
{
	return imageName_;
}

result MultispectralImage::AddBand(const StringA& fileName, const StringA& bandName)
{
	CPGMBitmap* pBitmap = new CPGMBitmap;

	result resultCode = pBitmap->LoadPGMBitmap(fileName.c_str());
	if (FAILED(resultCode))
	{
		delete pBitmap;
		return resultCode;
	}

	IPGMBitmap* piBitmap = QueryTool<CPGMBitmap, IPGMBitmap>::QueryInterface(pBitmap, IID_IPGMBitmap);

	Band* pBand = new Band(piBitmap, fileName, bandName);

	IDataBitmap* piDataBitmap = QueryTool<IPGMBitmap, IDataBitmap>::QueryInterface(pBitmap, IID_IDataBitmap);

	width_ = piDataBitmap->GetWidth();
	height_ = piDataBitmap->GetHeight();
		
	piDataBitmap->Release();
	piBitmap->Release();

	resultCode = piBandsContainer_->Add(pBand);
	if (FAILED(resultCode))
	{
		delete pBand;
		return resultCode;
	} 

	return S_OK;
}

uint MultispectralImage::GetBandsCount()
{
	return piBandsContainer_->Size();
}

IBandsEnumerator* MultispectralImage::GetBandsEnumerator()
{
	return piBandsContainer_->Clone();
}

uint MultispectralImage::GetWidth()
{
	return width_;
}

uint MultispectralImage::GetHeight()
{
	return height_;
}

// Private Tools
//////////////////////////////////////////////////////////////////////////
void MultispectralImage::CleanUp()
{
	IBandsEnumerator* piBands = piBandsContainer_->Clone();
	for (bool hasBands = piBands->SelectFirst();hasBands;hasBands = piBands->SelectNext())
	{
		Band* pBand = piBands->GetSelected();
        delete pBand;		
	}
	piBands->Release();

	if (piBandsContainer_)
		piBandsContainer_->Release();
}

}
