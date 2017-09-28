#ifndef TIFFFACTORY_H__SERIALIZATION__INCLUDED_
#define TIFFFACTORY_H__SERIALIZATION__INCLUDED_

namespace Serialization
{

	class TiffFactory
	{
	public:

		static result LoadImage(const StringA& fileName, IDataBitmap* piDataBitmap);

	};

}

#endif // !TIFFFACTORY_H__SERIALIZATION__INCLUDED_
