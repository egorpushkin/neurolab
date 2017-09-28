#ifndef TRAINDATASERIALIZER_H__SERIALIZATION__INCLUDED_
#define TRAINDATASERIALIZER_H__SERIALIZATION__INCLUDED_

namespace Serialization
{

	class TrainDataSerializer
	{
	public:

		static result StoreData(const StringA& fileName, IDataFile* piDataFile);

	};

}

#endif // !TRAINDATASERIALIZER_H__SERIALIZATION__INCLUDED_
