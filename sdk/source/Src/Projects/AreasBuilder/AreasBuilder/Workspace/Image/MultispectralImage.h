#ifndef MULTISPECTRALIMAGE_H__WORKSPACE__INCLUDED_
#define MULTISPECTRALIMAGE_H__WORKSPACE__INCLUDED_

namespace Workspace
{

class MultispectralImage
{
public:
	MultispectralImage();    
	virtual ~MultispectralImage();

	// Public Tools
	//////////////////////////////////////////////////////////////////////////
    virtual	void				SetImageName(const StringA& imageName);
	virtual	StringA				GetImageName();

	virtual	result				AddBand(const StringA& fileName, const StringA& bandName);
	
	virtual uint				GetBandsCount();
	virtual IBandsEnumerator*	GetBandsEnumerator();

	virtual uint				GetWidth();
	virtual uint				GetHeight();

private:
	// Private Tools
	//////////////////////////////////////////////////////////////////////////
    void						CleanUp();

private:
	StringA						imageName_;
	IBandsContainer*			piBandsContainer_;

	uint						width_;
	uint						height_;
};

}

#endif // !MULTISPECTRALIMAGE_H__WORKSPACE__INCLUDED_
