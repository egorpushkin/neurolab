#ifndef FRAGMENTS_H__DATAGENERATOR__INCLUDED_
#define FRAGMENTS_H__DATAGENERATOR__INCLUDED_

namespace Generator
{

	// Fragments declaration
	class Fragments 
	{
	public:

        // Public interface
		static result CutFragments(
			Workspace::MultispectralImage* pImage,
			Areas::AreasTool* pAreasTool,
			uint count,
			uint width,
			uint height,
			IDataFactory* piInputBand,
			IDataFactory* piInput,
			IDataFactory* piOutput,
			IDataFile* piDataFile);

	private:
	
        // Private interface
		static uint Random(uint lo, uint hi);

		static result MoveFactoryData(
			IDataFactory* piSourceDataFactory, 
			uint sourceOffset, 
			uint length, 
			IDataFactory* piDestinationDataFactory, 
			uint destinationOffset);

		static result ExportFragmentCore(
			Workspace::MultispectralImage* pImage, 
			uint xOffset, uint yOffset, 
			uint width, uint height, 
			IDataFactory* piInputBand,
			IDataFactory* piInput);

		static result ProcessCutAreaCore(
			Workspace::MultispectralImage* pImage,
			Areas::AreasTool* pAreasTool,
			uint areaIndex,
			uint count,
			uint width,
			uint height,
			IDataFactory* piInputBand,
			IDataFactory* piInput,
			IDataFactory* piOutput,
			IDataFile* piDataFile);




		



	};

}

#endif // !FRAGMENTS_H__DATAGENERATOR__INCLUDED_
