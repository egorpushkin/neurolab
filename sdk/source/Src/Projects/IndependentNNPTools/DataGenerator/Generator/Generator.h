#ifndef GENERATOR_H__DATAGENERATOR__INCLUDED_
#define GENERATOR_H__DATAGENERATOR__INCLUDED_

namespace Generator
{

	// TrainDataGenerator declaration
	class TrainDataGenerator 
	{
	public:

		TrainDataGenerator();
		~TrainDataGenerator();

		// Public interface
		result Generate(Workspace::IAreasProject* piProject, Areas::AreasTool* pAreas, IDataFile* piDataFile);

	};

}

#endif // !GENERATOR_H__DATAGENERATOR__INCLUDED_
