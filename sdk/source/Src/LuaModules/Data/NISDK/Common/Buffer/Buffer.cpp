#include "Common/Includes.h"

#include "Buffer.h"

namespace NISDK
{

	Buffer::Buffer()
		: data_(NULL)
		, length_(0)
		, release_(false)
	{
	}

	Buffer::~Buffer()
	{
		Release();
	}

	void Buffer::SetData(void* data, uint length, bool release)
	{
		Release();

		data_ = data;
		length_ = length;
		release_ = release;
	}

	void* Buffer::GetData()
	{
		return data_;
	}

	uint Buffer::GetLength()
	{
		return length_;
	}

	// Private
	//////////////////////////////////////////////////////////////////////////
	void Buffer::Release()
	{
		if ( !release_ || !data_ || length_ == 0 )
			return;

		delete[] data_;
		data_ = NULL;
	}

} // namespace NISDK
