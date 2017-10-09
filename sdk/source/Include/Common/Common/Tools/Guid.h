#ifndef GUID_H__TOOLS__COMMON__INCLUDED_
#define GUID_H__TOOLS__COMMON__INCLUDED_

inline result CLSIDFromString(const StringA& s, LPCLSID id)
{
	byte table[256];

	// validate the CLSID string 
	if (s.size() != 38)
		return E_FAIL;
	
	if ((s[0]!='{') || (s[9]!='-') || (s[14]!='-') || (s[19]!='-') || (s[24]!='-') || (s[37]!='}'))
		return E_FAIL;

	for (int i = 1; i < 37; i++) 
	{
		if ((i == 9)||(i == 14)||(i == 19)||(i == 24)) 
			continue;
		if (!(((s[i] >= '0') && (s[i] <= '9'))  ||
			((s[i] >= 'a') && (s[i] <= 'f'))  ||
			((s[i] >= 'A') && (s[i] <= 'F'))))
			return E_FAIL;
	}

	// quick lookup table 
	memset(table, 0, 256);
	for (i = 0; i < 10; i++) 
		table['0' + i] = (byte)i;
	
	for (i = 0; i < 6; i++) 
	{
		table['A' + i] = (byte)(i + 10);
		table['a' + i] = (byte)(i + 10);
	}

	// in form {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}
	id->Data1 = (table[s[1]] << 28 | table[s[2]] << 24 | table[s[3]] << 20 | table[s[4]] << 16 |
		table[s[5]] << 12 | table[s[6]] << 8  | table[s[7]] << 4  | table[s[8]]);
	id->Data2 = table[s[10]] << 12 | table[s[11]] << 8 | table[s[12]] << 4 | table[s[13]];
	id->Data3 = table[s[15]] << 12 | table[s[16]] << 8 | table[s[17]] << 4 | table[s[18]];

	/* these are just sequential bytes */
	id->Data4[0] = table[s[20]] << 4 | table[s[21]];
	id->Data4[1] = table[s[22]] << 4 | table[s[23]];
	id->Data4[2] = table[s[25]] << 4 | table[s[26]];
	id->Data4[3] = table[s[27]] << 4 | table[s[28]];
	id->Data4[4] = table[s[29]] << 4 | table[s[30]];
	id->Data4[5] = table[s[31]] << 4 | table[s[32]];
	id->Data4[6] = table[s[33]] << 4 | table[s[34]];
	id->Data4[7] = table[s[35]] << 4 | table[s[36]];

	return S_OK;
}

inline result StringFromCLSID(const CLSID* id, StringA& s)
{
	static const char hex[] = "0123456789abcdef";	

	if (!id)
		return E_FAIL;

	s.resize(38);
	sprintf(const_cast<char*>(s.c_str()), "{%08x-%04x-%04x-%02x%02x-",
		id->Data1, id->Data2, id->Data3,
		id->Data4[0], id->Data4[1]);
	
	char* str = &s[25];

	// 6 hex bytes 
	for (int i = 2; i < 8; i++) 
	{
		*str++ = hex[id->Data4[i]>>4];
		*str++ = hex[id->Data4[i] & 0xf];
	}
	
	*str++ = '}';
	*str++ = '\0';

	return S_OK;
}

#endif // !GUID_H__TOOLS__COMMON__INCLUDED_
