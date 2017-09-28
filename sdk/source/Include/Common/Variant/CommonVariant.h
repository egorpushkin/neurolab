#ifndef COMMONVARIANT_H__COMMON__INCLUDED_
#define COMMONVARIANT_H__COMMON__INCLUDED_

typedef struct tagCommonVariant CommonVariant;

typedef unsigned short CommonVarType;
typedef bool CommonVariant_bool;
typedef bool _CommonVariant_bool;

/*
typedef struct tagDEC {
	ushort wReserved;
	union {
		struct {
			byte scale;
			byte sign;
		};
		ushort signscale;
	};
	ulong Hi32;
	union {
		struct {
			ulong Lo32;
			ulong Mid32;
		};
		ulonglong Lo64;
	};
} DECIMAL;
*/

#define __VARIANT_NAME_1
#define __VARIANT_NAME_2
#define __VARIANT_NAME_3

struct tagCommonVariant
{
/*	union
	{ 
		struct __tagCommonVariant
		{ */
			CommonVarType				vt_;
			word						wReserved1_;
			word						wReserved2_;
			word						wReserved3_;

			union 
			{
				longlong                llval_;             // VT_I8. 
				long                    lVal_;              // VT_I4.
				byte                    bVal_;              // VT_UI1.
				short                   iVal_;              // VT_I2.
				float                   fltVal_;            // VT_R4.
				double                  dblVal_;            // VT_R8.
				CommonVariant_bool      boolVal_;           // VT_BOOL.
				_CommonVariant_bool     bool_;
				// SCODE                   scode_;             // VT_ERROR.
				// CY                      cyVal_;             // VT_CY.
				date                    date_;              // VT_DATE.
				// BSTR                    bstrVal_;           // VT_BSTR.
				ICommon                 * pcmnVal_;         // VT_COMMON.
				//IDispatch               * pdispVal_;        // VT_DISPATCH.
				//SAFEARRAY               * parray_;          // VT_ARRAY|*.
				byte                    * pbVal_;           // VT_BYREF|VT_UI1.
				short                   * piVal_;           // VT_BYREF|VT_I2.
				long                    * plVal_;           // VT_BYREF|VT_I4.
				longlong                * pllVal_;          // VT_BYREF|VT_I8.
				float                   * pfltVal_;         // VT_BYREF|VT_R4.
				double                  * pdblVal_;         // VT_BYREF|VT_R8.
				CommonVariant_bool      * pboolVal_;        // VT_BYREF|VT_BOOL.
				_CommonVariant_bool     * pbool_;
				// SCODE                   * pscode_;          // VT_BYREF|VT_ERROR.
				// CY                      * pcyVal_;          // VT_BYREF|VT_CY.
				// DATE                    * pdate_;           // VT_BYREF|VT_DATE.
				// BSTR                    * pbstrVal_;        // VT_BYREF|VT_BSTR.
				ICommon                 ** ppcmnVal_;       // VT_BYREF|VT_COMMON.
				// IDispatch               ** ppdispVal_;      // VT_BYREF|VT_DISPATCH.
				// SAFEARRAY               ** pparray_;        // VT_ARRAY|*.
				CommonVariant           * pvarVal_;         // VT_BYREF|VT_VARIANT.
				pvoid                   * byref_;           // Generic ByRef.
				char                    cVal_;              // VT_I1.
				ushort                  uiVal_;             // VT_UI2.
				ulong                   ulVal_;             // VT_UI4.
				ulonglong               ullVal_;            // VT_UI8.
				int                     intVal_;            // VT_INT.
				uint                    uintVal_;           // VT_UINT.
				//DECIMAL                 * pdecVal_;         // VT_BYREF|VT_DECIMAL.
				char                    * pcVal_;           // VT_BYREF|VT_I1.
				ushort                  * puiVal_;          // VT_BYREF|VT_UI2.
				ulong                   * pulVal_;          // VT_BYREF|VT_UI4.
				ulonglong               * pullVal_;         // VT_BYREF|VT_UI8.
				int                     * pintVal_;         // VT_BYREF|VT_INT.
				uint                    * puintVal_;        // VT_BYREF|VT_UINT.

				// struct __tagBRECORD
				// {
				//	PVOID				pvRecord_;
				//	IRecordInfo*		pRecInfo_;
				// } __tagBRECORD;
			} __VARIANT_NAME_3;
/*		} __VARIANT_NAME_2;
		DECIMAL							decVal;
	} 	__VARIANT_NAME_1;	*/

}; 

#endif // !COMMONVARIANT_H__COMMON__INCLUDED_
