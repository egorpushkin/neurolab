#ifndef WSCOMMON_H__WORKSPACE__INCLUDED_
#define WSCOMMON_H__WORKSPACE__INCLUDED_

// Including support of libxml2 engine for external serializers
//////////////////////////////////////////////////////////////////////////
#include <libxml/xmlmemory.h> 
#include <libxml/parser.h> 
#include <libxml/encoding.h> 
#include <libxml/xmlwriter.h> 

// Workspace common includes
//////////////////////////////////////////////////////////////////////////
#include "ErrorCodes.h"

#include "Image/Band.h"
#include "Image/MultispectralImage.h"
#include "Areas/MapConfig.h"

#include "Interfaces/IAreasProject.h"
#include "AreasProject.h"

#endif // !WSCOMMON_H__WORKSPACE__INCLUDED_
