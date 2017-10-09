#ifndef CMNELEMENT_H__BUILDERELEMENTS__INCLUDED_
#define CMNELEMENT_H__BUILDERELEMENTS__INCLUDED_

#define MAX_TITLE_LENGTH				256

class CCmnElement 
	: public NetworkImportingKit::IElement
	, public IStorageController
{
public:
	CCmnElement();
	virtual ~CCmnElement();

protected:
	// Custom tools
	result					RemoveElement();
	result					SetAddConnectionState(uint state);

	// IStorageController declarations section
	virtual result			Serialize(DataProcessingKit::FILEDev& fileDev, bool loading);

	// IElement declarations section
	virtual void			SetElementID(uint eleemntId);
	virtual uint			GetElementID() const;

	virtual	uint			GetElementType() const;

	virtual void			SetSysName(const StringA& name);
	virtual const StringA&	GetSysName() const;

	virtual void			SetSysTitle(const StringA& title);
	virtual const StringA&	GetSysTitle() const;	

	virtual void			SetShortName(const StringA& name);
	virtual const StringA&	GetShortName() const;

	virtual void CommandNotify(wparam wParam, lparam lParam);

protected:
	uint					elementId_;

	StringA					sysName_;
	StringA					sysTitle_;
	StringA					sysShortName_;

	int						elementType_;
};

#endif // !CMNELEMENT_H__BUILDERELEMENTS__INCLUDED_
