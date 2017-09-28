#include "../ConsoleHelpersKit/ConsoleHelpersKit.h"

#include "SerializeTiffFactory.h"

#include "tiffio.h"

result SerializeTiffFactory::Serialize(const StringA& fileName, IDataFactory* piDataFactory, bool loading)
{
	result r = S_OK;

	if ( loading )
	{
		r = Load(fileName, piDataFactory);
	} 
	else
	{
		r = Store(fileName, piDataFactory);
	}

	return r;
}

// Internal serialization helpers
result SerializeTiffFactory::Store(const StringA& fileName, IDataFactory* piDataFactory)
{
	TIFF* image = TIFFOpen(fileName.c_str(), "w");
	if ( !image )
		return E_FAIL;

	uint32 width = piDataFactory->GetDataLength(), height = 1;

	TIFFSetField(image, TIFFTAG_IMAGEWIDTH, width);
	TIFFSetField(image, TIFFTAG_IMAGELENGTH, height);
	TIFFSetField(image, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
	TIFFSetField(image, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(image, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
	TIFFSetField(image, TIFFTAG_BITSPERSAMPLE, 8);
	TIFFSetField(image, TIFFTAG_SAMPLESPERPIXEL, 1);

	size_t npixels = width * height;

	unsigned char* raster = (unsigned char*) _TIFFmalloc((tsize_t)(npixels * sizeof (unsigned char)));

	for ( uint i = 0 ; i < npixels ; ++i )	
	{
		float value = piDataFactory->GetItemData(i);
		value *= 255.0f;		
		unsigned char sample = (unsigned char)value;
        raster[i] = sample;
	}

	if ( TIFFWriteEncodedStrip(image, 0, raster, width * height * sizeof(unsigned char)) == 0 )
	{
		TIFFClose(image);
		return E_FAIL;
	}

	TIFFClose(image);

	return S_OK;
}

result SerializeTiffFactory::Load(const StringA& fileName, IDataFactory* piDataFactory)
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

	piDataFactory->CreateFactory((uint)npixels);
	
	for ( uint i = 0 ; i < npixels ; ++i )	
		piDataFactory->SetItemData(i, (float)(raster[i] & 0x000000ff));

	_TIFFfree(raster);
	TIFFClose(image);

	return S_OK;
}
