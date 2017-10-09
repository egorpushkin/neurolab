#include "Common/ScriptsMachine.h"

#include "Path.h"

namespace ScriptsMachine
{

	StringA GetFilePath(const StringA& filename)
	{
		size_t pos1 = filename.rfind('\\');
		size_t pos2 = filename.rfind('/');

		if (pos1 == StringA::npos && pos2 == StringA::npos)
			return StringA();
        
		if (pos1 == StringA::npos)
			pos1 = pos2;

		if (pos2 > pos1 && pos2 != StringA::npos)
			pos1 = pos2;

		if (pos1)
			--pos1;
		while ( ( filename.at(pos1) == '\\' || filename.at(pos1) == '/' ) && ( pos1 > 0 ) )
			--pos1;

		return filename.substr(0, pos1 + 1);       
	}



} // namespace ScriptsMachine
