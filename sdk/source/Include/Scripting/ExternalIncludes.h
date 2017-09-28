#ifndef EXTERNALINCLUDES_H__SCRIPTINGKIT__INCLUDED_
#define EXTERNALINCLUDES_H__SCRIPTINGKIT__INCLUDED_

/**
 * @file ExternalIncludes.h
 * @short Kit requirements were included here.
 * 
 * Several redifinitions were made.
 */

#include "../Common/CommonKit.h"
using namespace CommonKit;

namespace MinCOM
{	
	// Connect symbols declared in CommonKit
	using namespace CommonKit;
}

#include "../Common/ContainerNew/Container.h"

#include "../Components/ComponentsKit.h"

#endif // !EXTERNALINCLUDES_H__SCRIPTINGKIT__INCLUDED_
