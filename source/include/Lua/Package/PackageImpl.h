#ifndef PACKAGEIMPL_H__LUAKIT__INCLUDED_
#define PACKAGEIMPL_H__LUAKIT__INCLUDED_

namespace LuaKit
{

	class PackageImpl 
	{
	public:

		typedef std::vector< ApiImpl* > ApisVector_;

		PackageImpl()
			: packageName_("")
			, version_("")
			, bindingsVer_("")
			, groupName_("")
			, apis_()
			//, globalApi_({NULL, NULL})
		{
			globalApi_[0].name = NULL;
			globalApi_[0].func = NULL;
		}

		virtual ~PackageImpl()
		{
		}

		// Public interface
		virtual void Open(lua_State *L)
		{
			luaL_openlib(L, packageName_, globalApi_, 0);

		#ifdef _DEBUG
			lua_pushstring(L, "_DEBUG");
			lua_pushboolean(L, 1);
			lua_rawset(L, -3);
		#endif

			lua_pushstring(L, "_VERSION");
			lua_pushstring(L, version_);
			lua_rawset(L, -3);

			lua_pushstring(L, "_BINDINGS");
			lua_pushstring(L, bindingsVer_);
			lua_rawset(L, -3);

			ApisVector_::const_iterator iter = apis_.begin();
			ApisVector_::const_iterator end = apis_.end();

			for ( ; iter != end ; ++iter )
			{
				(*iter)->Open(L);
			}            
		}

		void SetInfo(const char* name, const char* ver, const char* bind, const char* group)
		{
			packageName_ = name;
			version_ = ver;
			bindingsVer_ = bind;
			groupName_ = group;
		}

		const char* GetGroupName()
		{
			return groupName_;
		}

		void AddApi(ApiImpl* api)
		{
			if ( !api )
				return;

			api->SetGroupName(groupName_);

			apis_.push_back(api);
		}

	protected:

		const char* packageName_;
		const char* version_;
		const char* bindingsVer_;
		const char* groupName_;
	
		ApisVector_ apis_;		

		luaL_reg globalApi_[1];

	};
	
} // namespace LuaKit

#endif // !PACKAGEIMPL_H__LUAKIT__INCLUDED_
