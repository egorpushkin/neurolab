#ifndef ICOMMON_H__MINCOM__COMMONKIT__INCLUDED_
#define ICOMMON_H__MINCOM__COMMONKIT__INCLUDED_

interface ICommon
{
    virtual result          QueryInterface(REFIID iid, void** ppObject) = 0;

	virtual ulong			AddRef() = 0;
    virtual ulong           Release() = 0;
};

typedef ComPtr< ICommon > ICommonPtr;
typedef const ICommonPtr& ICommonRef;

#endif // !ICOMMON_H__MINCOM__COMMONKIT__INCLUDED_
