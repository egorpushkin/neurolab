#ifndef CALLBACK_H__DRAWING__LUA_PACKAGE__INCLUDED_
#define CALLBACK_H__DRAWING__LUA_PACKAGE__INCLUDED_

namespace Drawing
{

	class Callback 
		: public DrawingControl::EventsImpl
	{
	public:

		Callback(DrawingControl::IControlHolderRef controlHolder, lua_State* L);
		virtual ~Callback();

		// IEvents section
		virtual void OnInit();
		virtual void OnPaint(Gdiplus::Graphics* /* pGraphics */);
		virtual void OnTimer(uint /* nIDEvent */);

	private:

		DrawingControl::IControlHolderPtr controlHolder_;

		lua_State* L_;
		lua_State* LChild_;

	};

} // namespace Drawing

#endif // !CALLBACK_H__DRAWING__LUA_PACKAGE__INCLUDED_
