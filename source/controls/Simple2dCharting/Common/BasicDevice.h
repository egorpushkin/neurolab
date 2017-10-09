#ifndef BASICDEVICE_H__S2DCHARTING__INCLUDED_
#define BASICDEVICE_H__S2DCHARTING__INCLUDED_

namespace Simple2dCharting
{

	typedef unsigned long Color;

	typedef enum 
	{
		FontStyleRegular = 0,
		FontStyleBold = 1,
		FontStyleItalic = 2,
		FontStyleBoldItalic = 3,
		FontStyleUnderline = 4,
		FontStyleStrikeout = 8
	} FontStyle;

	class BasicDevice
	{
	public:

		BasicDevice();
		virtual ~BasicDevice();

		// Pure interface
		virtual void ConstructFromHandle(void* pWnd, void* pHandle) = 0;
		virtual void DumpContext() = 0;

		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;
		
		virtual void FillRectangle(Color color, float x, float y, float width, float height) = 0;
		virtual void DrawLine(Color color, float fromX, float fromY, float toX, float toY, float thickness = 1.0) = 0;
		virtual void DrawString(Color color, const std::string& font, float size, FontStyle style, float x, float y, const std::string& text) = 0;

	public:

		static Color AliceBlue; // 0xFFF0F8FF
		static Color AntiqueWhite; // 0xFFFAEBD7    
		static Color Aqua; // 0xFF00FFFF    
		static Color Aquamarine; // 0xFF7FFFD4    
		static Color Azure; // 0xFFF0FFFF    
		static Color Beige; // 0xFFF5F5DC    
		static Color Bisque; // 0xFFFFE4C4    
		static Color Black; // 0xFF000000    
		static Color BlanchedAlmond; // 0xFFFFEBCD    
		static Color Blue; // 0xFF0000FF    
		static Color BlueViolet; // 0xFF8A2BE2    
		static Color Brown; // 0xFFA52A2A    
		static Color BurlyWood; // 0xFFDEB887    
		static Color CadetBlue; // 0xFF5F9EA0    
		static Color Chartreuse; // 0xFF7FFF00    
		static Color Chocolate; // 0xFFD2691E    
		static Color Coral; // 0xFFFF7F50    
		static Color CornflowerBlue; // 0xFF6495ED    
		static Color Cornsilk; // 0xFFFFF8DC    
		static Color Crimson; // 0xFFDC143C    
		static Color Cyan; // 0xFF00FFFF    
		static Color DarkBlue; // 0xFF00008B    
		static Color DarkCyan; // 0xFF008B8B    
		static Color DarkGoldenrod; // 0xFFB8860B    
		static Color DarkGray; // 0xFFA9A9A9    
		static Color DarkGreen; // 0xFF006400    
		static Color DarkKhaki; // 0xFFBDB76B    
		static Color DarkMagenta; // 0xFF8B008B    
		static Color DarkOliveGreen; // 0xFF556B2F    
		static Color DarkOrange; // 0xFFFF8C00    
		static Color DarkOrchid; // 0xFF9932CC    
		static Color DarkRed; // 0xFF8B0000    
		static Color DarkSalmon; // 0xFFE9967A    
		static Color DarkSeaGreen; // 0xFF8FBC8B    
		static Color DarkSlateBlue; // 0xFF483D8B    
		static Color DarkSlateGray; // 0xFF2F4F4F    
		static Color DarkTurquoise; // 0xFF00CED1    
		static Color DarkViolet; // 0xFF9400D3    
		static Color DeepPink; // 0xFFFF1493    
		static Color DeepSkyBlue; // 0xFF00BFFF    
		static Color DimGray; // 0xFF696969    
		static Color DodgerBlue; // 0xFF1E90FF    
		static Color Firebrick; // 0xFFB22222    
		static Color FloralWhite; // 0xFFFFFAF0    
		static Color ForestGreen; // 0xFF228B22    
		static Color Fuchsia; // 0xFFFF00FF    
		static Color Gainsboro; // 0xFFDCDCDC    
		static Color GhostWhite; // 0xFFF8F8FF    
		static Color Gold; // 0xFFFFD700    
		static Color Goldenrod; // 0xFFDAA520    
		static Color Gray; // 0xFF808080    
		static Color Green; // 0xFF008000    
		static Color GreenYellow; // 0xFFADFF2F    
		static Color Honeydew; // 0xFFF0FFF0    
		static Color HotPink; // 0xFFFF69B4    
		static Color IndianRed; // 0xFFCD5C5C    
		static Color Indigo; // 0xFF4B0082    
		static Color Ivory; // 0xFFFFFFF0    
		static Color Khaki; // 0xFFF0E68C    
		static Color Lavender; // 0xFFE6E6FA    
		static Color LavenderBlush; // 0xFFFFF0F5    
		static Color LawnGreen; // 0xFF7CFC00    
		static Color LemonChiffon; // 0xFFFFFACD    
		static Color LightBlue; // 0xFFADD8E6    
		static Color LightCoral; // 0xFFF08080    
		static Color LightCyan; // 0xFFE0FFFF    
		static Color LightGoldenrodYellow; // 0xFFFAFAD2    
		static Color LightGray; // 0xFFD3D3D3    
		static Color LightGreen; // 0xFF90EE90    
		static Color LightPink; // 0xFFFFB6C1    
		static Color LightSalmon; // 0xFFFFA07A    
		static Color LightSeaGreen; // 0xFF20B2AA    
		static Color LightSkyBlue; // 0xFF87CEFA    
		static Color LightSlateGray; // 0xFF778899    
		static Color LightSteelBlue; // 0xFFB0C4DE    
		static Color LightYellow; // 0xFFFFFFE0    
		static Color Lime; // 0xFF00FF00    
		static Color LimeGreen; // 0xFF32CD32    
		static Color Linen; // 0xFFFAF0E6    
		static Color Magenta; // 0xFFFF00FF    
		static Color Maroon; // 0xFF800000    
		static Color MediumAquamarine; // 0xFF66CDAA    
		static Color MediumBlue; // 0xFF0000CD    
		static Color MediumOrchid; // 0xFFBA55D3    
		static Color MediumPurple; // 0xFF9370DB    
		static Color MediumSeaGreen; // 0xFF3CB371    
		static Color MediumSlateBlue; // 0xFF7B68EE    
		static Color MediumSpringGreen; // 0xFF00FA9A    
		static Color MediumTurquoise; // 0xFF48D1CC    
		static Color MediumVioletRed; // 0xFFC71585    
		static Color MidnightBlue; // 0xFF191970    
		static Color MintCream; // 0xFFF5FFFA    
		static Color MistyRose; // 0xFFFFE4E1    
		static Color Moccasin; // 0xFFFFE4B5    
		static Color NavajoWhite; // 0xFFFFDEAD    
		static Color Navy; // 0xFF000080    
		static Color OldLace; // 0xFFFDF5E6    
		static Color Olive; // 0xFF808000    
		static Color OliveDrab; // 0xFF6B8E23    
		static Color Orange; // 0xFFFFA500    
		static Color OrangeRed; // 0xFFFF4500    
		static Color Orchid; // 0xFFDA70D6    
		static Color PaleGoldenrod; // 0xFFEEE8AA    
		static Color PaleGreen; // 0xFF98FB98    
		static Color PaleTurquoise; // 0xFFAFEEEE    
		static Color PaleVioletRed; // 0xFFDB7093    
		static Color PapayaWhip; // 0xFFFFEFD5    
		static Color PeachPuff; // 0xFFFFDAB9    
		static Color Peru; // 0xFFCD853F    
		static Color Pink; // 0xFFFFC0CB    
		static Color Plum; // 0xFFDDA0DD    
		static Color PowderBlue; // 0xFFB0E0E6    
		static Color Purple; // 0xFF800080    
		static Color Red; // 0xFFFF0000    
		static Color RosyBrown; // 0xFFBC8F8F    
		static Color RoyalBlue; // 0xFF4169E1    
		static Color SaddleBrown; // 0xFF8B4513    
		static Color Salmon; // 0xFFFA8072    
		static Color SandyBrown; // 0xFFF4A460    
		static Color SeaGreen; // 0xFF2E8B57    
		static Color SeaShell; // 0xFFFFF5EE    
		static Color Sienna; // 0xFFA0522D    
		static Color Silver; // 0xFFC0C0C0    
		static Color SkyBlue; // 0xFF87CEEB    
		static Color SlateBlue; // 0xFF6A5ACD    
		static Color SlateGray; // 0xFF708090    
		static Color Snow; // 0xFFFFFAFA    
		static Color SpringGreen; // 0xFF00FF7F    
		static Color SteelBlue; // 0xFF4682B4    
		static Color Tan; // 0xFFD2B48C    
		static Color Teal; // 0xFF008080    
		static Color Thistle; // 0xFFD8BFD8    
		static Color Tomato; // 0xFFFF6347    
		static Color Transparent; // 0x00FFFFFF    
		static Color Turquoise; // 0xFF40E0D0    
		static Color Violet; // 0xFFEE82EE    
		static Color Wheat; // 0xFFF5DEB3    
		static Color White; // 0xFFFFFFFF    
		static Color WhiteSmoke; // 0xFFF5F5F5    
		static Color Yellow; // 0xFFFFFF00    
		static Color YellowGreen; // 0xFF9ACD32    

	}; // BasicDevice

	typedef Loki::StrongPtr< BasicDevice > BasicDevicePtr;
	typedef const BasicDevicePtr& BasicDeviceRef;
	
} // Simple2dCharting

#endif // !BASICDEVICE_H__S2DCHARTING__INCLUDED_
