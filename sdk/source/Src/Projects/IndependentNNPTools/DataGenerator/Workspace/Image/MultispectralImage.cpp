#include "../../PrecompiledHeader.h"

#include "MultispectralImage.h"

#include "Serialization/TiffFactory.h"

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
	IPGMBitmap* piPGMBitmap = 
		CConstructTool<CPGMBitmap, IPGMBitmap>::ConstructObject(IID_IPGMBitmap);
	IDataBitmap* piDataBitmap = 
		QueryTool<IPGMBitmap, IDataBitmap>::QueryInterface(piPGMBitmap, IID_IDataBitmap);

	result resultCode = S_OK;

	if ( fileName.rfind(".pgm") != StringA::npos )
	{
		resultCode = piPGMBitmap->LoadPGMBitmap(fileName.c_str());
	}
	else if ( fileName.rfind(".tiff") != StringA::npos )
	{        
		resultCode = Serialization::TiffFactory::LoadImage(fileName, piDataBitmap);
	}

	if ( FAILED(resultCode) )
	{
		piPGMBitmap->Release();
		piDataBitmap->Release();
		return resultCode;
	}

	Band* pBand = new Band(piPGMBitmap, fileName, bandName);

	width_ = piDataBitmap->GetWidth();
	height_ = piDataBitmap->GetHeight();

	piDataBitmap->Release();
	piPGMBitmap->Release();

	if ( FAILED(piBandsContainer_->Add(pBand)) )
	{
		delete pBand;
		return E_FAIL;
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
