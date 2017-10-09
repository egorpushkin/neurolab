#include "Common/Includes.h"

#include "Point.h"

#include "Line.h"
#include "Line_template.h"

namespace Simple2dCharting 
{

	// explicit instantiations
	template class Line< int >;
	template class Line< float >;

} // namespace Simple2dCharting
