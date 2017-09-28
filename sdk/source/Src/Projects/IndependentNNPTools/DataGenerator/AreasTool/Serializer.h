#ifndef SERIALIZER_H__AREASTOOL__INCLUDED_
#define SERIALIZER_H__AREASTOOL__INCLUDED_

namespace Areas
{

	// Serializer declaration
	class Serializer 
	{
	public:
		Serializer();
		~Serializer();

		// Public interface
		result LoadAreas(const StringA& fileName, AreasTool* pAreas);

	};

}

#endif // !SERIALIZER_H__AREASTOOL__INCLUDED_
