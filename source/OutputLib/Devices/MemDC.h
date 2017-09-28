#pragma once

class DLL_FUNC_DECLARE CDC;
class DLL_FUNC_DECLARE CBitmap;
class DLL_FUNC_DECLARE CRect;

class DLL_FUNC_DECLARE CMemDC : public CDC
{
public:
	
	CMemDC():CDC()
	{
		mHasDC = false;
	}
	CMemDC(CDC *FromDC) : CDC()
	{
		ASSERT(FromDC != NULL);
		mFromDC = FromDC;
		CreateCompatibleDC(mFromDC);
			
		mHasDC = !FromDC->IsPrinting();
		if (mHasDC)
		{
			FromDC->GetClipBox(&mRect);
			mBitmap.CreateCompatibleBitmap(mFromDC,mRect.Width(),mRect.Height());
			mOldBitmap = SelectObject(&mBitmap);
			SetWindowOrg(mRect.left, mRect.top);
			BitBlt(mRect.left,mRect.top,mRect.Width(),mRect.Height(),mFromDC,	mRect.left,mRect.top,SRCCOPY);
		}	
		else        
        {
            m_bPrinting = FromDC->m_bPrinting;
            m_hDC       = FromDC->m_hDC;
            m_hAttribDC = FromDC->m_hAttribDC;
        }
	}

	virtual ~CMemDC()
	{
		if (mHasDC)
		{
			mFromDC->BitBlt(mRect.left,mRect.top,mRect.Width(),mRect.Height(),this,	mRect.left,mRect.top,SRCCOPY);
			
			SelectObject(mOldBitmap);
		} else {
            m_hDC = m_hAttribDC = NULL;
        }

	}

    CMemDC* operator->() {return this;}
        
    operator CMemDC*() {return this;}

private:
	bool	bNoCreate;
	CBitmap	*mOldBitmap;
	CDC		*mFromDC;
	CBitmap	mBitmap;
	int		mWidth,mHeight;
	bool	mHasDC;
	CRect	mRect;
};