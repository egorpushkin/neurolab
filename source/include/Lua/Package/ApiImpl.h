#ifndef APIIMPL_H__LUAKIT__INCLUDED_
#define APIIMPL_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	class ApiImpl 
	{
	public:

		typedef Loki::StrongPtr< 
			luaL_reg, 
			true,  
			Loki::TwoRefCounts,
			Loki::DisallowConversion,
			Loki::AssertCheck,
			Loki::CantResetWithStrong,
			Loki::DeleteArray
		> RegSmartArray_;
		
		typedef Loki::StrongPtr< 
			luaL_const, 
			true,  
			Loki::TwoRefCounts,
			Loki::DisallowConversion,
			Loki::AssertCheck,
			Loki::CantResetWithStrong,
			Loki::DeleteArray
		> ConstSmartArray_;

		typedef std::vector< luaL_reg > RegSmartVector_;
		typedef std::vector< luaL_const > ConstSmartVector_;		

		ApiImpl()
			: className_("")
			, groupName_("")
			, globalApi_()
			, objectApi_()
			, consts_()
		{
		}
		virtual ~ApiImpl()
		{
		}

		// Public interface
		virtual void Open(lua_State *L)
		{
			RegSmartArray_ objArray = PrepareArray<luaL_reg, RegSmartVector_, RegSmartArray_>(objectApi_);
				
			auxiliar_newclass(L, className_, objArray.GetPointer());
			auxiliar_add2group(L, className_, groupName_);

			RegSmartArray_ globArray = PrepareArray<luaL_reg, RegSmartVector_, RegSmartArray_>(globalApi_);

			luaL_openlib(L, NULL, globArray.GetPointer(), 0);  

			if ( consts_.size() > 0 )
			{
				ConstSmartArray_ constArray = PrepareArray<luaL_const, ConstSmartVector_, ConstSmartArray_>(consts_);
				
				luaL_openenum(L, constArray.GetPointer());
			}
		}

		void SetClassName(const char* name)
		{
			className_ = name;
		}

		const char* GetClassName() const 
		{
			return className_;
		}

		void SetGroupName(const char* name)
		{
			groupName_ = name;
		}

		const char* GetGroupName()
		{
			return groupName_;
		}

		void AddGlobal(const char* name, lua_CFunction func)
		{
			luaL_reg reg = {name, func}; 
			globalApi_.push_back(reg);
		}

		void AddMethod(const char* name, lua_CFunction func)
		{
			luaL_reg reg = {name, func}; 
			objectApi_.push_back(reg);
		}

		void AddConst(const char* name, float value)
		{
			luaL_const reg = {name, value}; 
			consts_.push_back(reg);
		}

	protected:

		// Protected interface
		template
		<
			class T,
			class SmartVector,
			class SmartArray
		>
		SmartArray PrepareArray(const SmartVector& regVector)
		{
			const size_t requiredLength = regVector.size() + 1;

			T* regArray = new T[requiredLength];

			SmartVector::const_iterator iter = regVector.begin();
			SmartVector::const_iterator end = regVector.end();

			for ( unsigned int i = 0 ; iter != end ; ++iter , ++i )
			{
				regArray[i].name = (*iter).name;
				regArray[i].func = (*iter).func;
			}

			regArray[requiredLength - 1].name = NULL;
			regArray[requiredLength - 1].func = NULL;

			return SmartArray(regArray);
		}

	protected:

		// Data members
		const char* className_;
		const char* groupName_;

		RegSmartVector_ globalApi_;
		RegSmartVector_ objectApi_; 
		ConstSmartVector_ consts_; 

	};

	typedef Loki::StrongPtr< ApiImpl, false > ApiImplWeak;
	typedef const ApiImplWeak& ApiImplWeakRef;

} // namespace LuaKit

#endif // !APIIMPL_H__LUAKIT__INCLUDED_
