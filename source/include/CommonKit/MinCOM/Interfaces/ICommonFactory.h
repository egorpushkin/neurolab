#ifndef ICOMMONFACTORY_H__MINCOM__COMMONKIT__INCLUDED_
#define ICOMMONFACTORY_H__MINCOM__COMMONKIT__INCLUDED_

interface ICommonFactory: public ICommon
{
    virtual result        LockServer(bool lock) = 0;
    virtual result        CreateInstance(REFIID iid, void** ppObject) = 0;
};

#endif // !ICOMMONFACTORY_H__MINCOM__COMMONKIT__INCLUDED_
