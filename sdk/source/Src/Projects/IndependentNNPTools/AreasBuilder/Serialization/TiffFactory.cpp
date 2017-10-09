#include "../ConsoleHelpersKit/ConsoleHelpersKit.h"

#include "TiffFactory.h"

#include "tiffio.h"

namespace Serialization
{

	result TiffFactory::LoadImage(const StringA& fileName, IDataBitmap* piDataBitmap)
	{
		TIFF* image = TIFFOpen(fileName.c_str(), "r");
		if ( !image )
			return E_FAIL;
		
		uint32 width, height;
		TIFFGetField(image, TIFFTAG_IMAGEWIDTH, &width);
		TIFFGetField(image, TIFFTAG_IMAGELENGTH, &height);

		uint16 bps, spp;
		TIFFGetField(image, TIFFTAG_BITSPERSAMPLE, &bps);
		TIFFGetField(image, TIFFTAG_SAMPLESPERPIXEL, &spp);

		if ( bps != 8 || spp != 1 )
			return E_FAIL;

		TIFFSetField(image, TIFFTAG_ORIENTATION, ORIENTATION_BOTLEFT);
		
		size_t npixels = width * height;
		uint32* raster = (uint32*) _TIFFmalloc((tsize_t)(npixels * sizeof (uint32)));

		if ( raster == NULL )
		{
			TIFFClose(image);
			return E_FAIL;
		}

		if ( !TIFFReadRGBAImage(image, width, height, raster, 0) ) 
		{
			_TIFFfree(raster);
			TIFFClose(image);
			return E_FAIL;
		}

		piDataBitmap->AllocateData(width, height, 1);
		
		for ( uint i = 0 ; i < npixels ; ++i )	
			*(((unsigned char*)piDataBitmap->GetData()) + i) = (unsigned char)(raster[i] & 0x000000ff);
			
		_TIFFfree(raster);
		TIFFClose(image);

		return S_OK;
	}

}
