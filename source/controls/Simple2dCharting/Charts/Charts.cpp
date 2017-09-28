#include "Common/Includes.h"

#include "Charts.h"

#include "Common/ContainerChart_template.h"

namespace Simple2dCharting 
{

	// explicit instantiations
	template class ContainerChart< IntegerPoint >;
	template class ContainerChart< FloatPoint >;

} // namespace Simple2dCharting
