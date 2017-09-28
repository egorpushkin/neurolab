#ifndef IHANDLER_H__PROJECTUI__INCLUDED_
#define IHANDLER_H__PROJECTUI__INCLUDED_

namespace ProjectUI
{

// {671fb075-8a33-4cf1-acba-d14fb83c6b1e} 
DEFINE_GUID(IID_IHandler, 
0x671fb075, 0x8a33, 0x4cf1, 0xac, 0xba, 0xd1, 0x4f, 0xb8, 0x3c, 0x6b, 0x1e);

interface IHandler : public ICommon
{
	virtual result			Invoke() = 0;
};

}

#endif // !IHANDLER_H__PROJECTUI__INCLUDED_
