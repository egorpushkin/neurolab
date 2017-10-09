#ifndef BUFFER_H__NISDK_DATA__INCLUDED_
#define BUFFER_H__NISDK_DATA__INCLUDED_

namespace NISDK
{

	class Buffer
	{
	public:
		Buffer();
		~Buffer();

		void SetData(void* data, uint length, bool release);
		void* GetData();
		uint GetLength();

	private:

		void Release();

		void* data_;
		uint length_;
		bool release_;

	};

} // namespace NISDK

#endif // !BUFFER_H__NISDK_DATA__INCLUDED_
