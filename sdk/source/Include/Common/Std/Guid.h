#ifndef GUID_H__MINCOM__STD__INCLUDED_
#define GUID_H__MINCOM__STD__INCLUDED_

namespace std
{

	__inline bool operator < (REFGUID left, REFGUID right)
	{
		if (memcmp(&left, &right, sizeof(sizeof(long) + sizeof(short) * 2 + sizeof(char) * 8)) < 0)
			return true;
		return false;
	}

}

#endif // !GUID_H__MINCOM__STD__INCLUDED_
