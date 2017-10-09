//	This code is a part of 'Console Helpers Kit' product.
//	Copyright (C) Scientific Software 2006
//	All rights reserved.

//	File name: Console.h
//	Description: Console helper object implementation.  

#ifndef CONSOLE_H__CONSOLEHELPERSKIT__INCLUDED_
#define CONSOLE_H__CONSOLEHELPERSKIT__INCLUDED_

class Console
{
public:
	static void EventNotify(const StringA& message, bool newLine = true)
	{
#ifndef DISPLAY_NO_MESSAGES
		printf(message.c_str());
		if (newLine) printf("\n");
#endif // !DISPLAY_NO_MESSAGES
	}
};

#endif // !CONSOLE_H__CONSOLEHELPERSKIT__INCLUDED_
