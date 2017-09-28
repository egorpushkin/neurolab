#ifndef CMNBUILDERELEMENT_H__BUILDERELEMENTS__INCLUDED_
#define CMNBUILDERELEMENT_H__BUILDERELEMENTS__INCLUDED_

class CCmnBuilderElement 
	: public BuilderElementsCommonKit::IBuilderElement
	, public IStorageController	
{
public:
	CCmnBuilderElement();
	virtual ~CCmnBuilderElement();

protected:
	// Custom render tools
	result					RenderLayer() const;

	// IStorageController declarations section
	virtual result			Serialize(FILEDev& fileDev, bool loading);

	// IBuilderElement implementations section
	virtual void			SetOutputControl(
		ExternalOutputEngine::IBuilderControl* piControl);
	virtual ExternalOutputEngine::IBuilderControl*	GetOutputControl() const;

	virtual void			SetElementPosition(
		const ExternalOutputEngine::BuilderPoint& point);
	virtual const ExternalOutputEngine::BuilderPoint&			
		GetElementPosition();

	virtual void			RenderElement() const;

	virtual bool			IsClicked(
		const ExternalOutputEngine::BuilderPoint& point) const;

	virtual void			SelectElement(bool select);
	virtual bool			IsSelected() const;

	virtual void			TrackPopupMenu(
		const ExternalOutputEngine::BuilderPoint& point) const;

	virtual const ExternalOutputEngine::BuilderPoint& 
		GetPositionForConnectedElement(
			const NetworkImportingKit::CConnection* pConnection);

protected:
	ExternalOutputEngine::IBuilderControl*		piBuilderControl_;

	ExternalOutputEngine::BuilderPoint		pntPosition_;
	bool					selected_;

	int						menuResourceId_;
	int						subMenuResourceId_;

	bool					layerBehaviour_;

	String					elementTextureActive_;
	String					elementTexturePassive_;

	int						imageWidth_;
	int						imageHeight_;

	int						shortNameOffset_;
	int						nameOffset_;
};

#endif // !CMNBUILDERELEMENT_H__BUILDERELEMENTS__INCLUDED_
