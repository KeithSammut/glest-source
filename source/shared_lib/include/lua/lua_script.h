// This file is part of Glest <https://github.com/Glest>
//
// Copyright (C) 2018  The Glest team
//
// Glest is a fork of MegaGlest <https://megaglest.org/>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>

#ifndef _SHARED_LUA_LUASCRIPT_H_
#define _SHARED_LUA_LUASCRIPT_H_

#include <string>
#include <lua.hpp>
#include "vec.h"
#include "xml_parser.h"
#include "leak_dumper.h"

using std::string;

using Shared::Graphics::Vec2i;
using Shared::Graphics::Vec4i;
using Shared::Graphics::Vec2f;
using Shared::Graphics::Vec3f;
using Shared::Graphics::Vec4f;

using Shared::Xml::XmlNode;

namespace Shared {
	namespace Lua {

		typedef lua_State LuaHandle;
		typedef int(*LuaFunction)(LuaHandle*);

		// =====================================================
		//	class LuaScript
		// =====================================================

		class LuaScript {
		private:
			LuaHandle *luaState;
			int argumentCount;
			string currentLuaFunction;
			bool currentLuaFunctionIsValid;
			string sandboxWrapperFunctionName;
			string sandboxCode;

			static bool disableSandbox;
			static bool debugModeEnabled;

			void DumpGlobals();

		public:
			LuaScript();
			~LuaScript();

			static void setDebugModeEnabled(bool value) {
				debugModeEnabled = value;
			}
			static bool getDebugModeEnabled() {
				return debugModeEnabled;
			}

			static void setDisableSandbox(bool value) {
				disableSandbox = value;
			}

			void loadCode(string code, string name);

			void beginCall(string functionName);
			void endCall();

			int runCode(const string code);
			void setSandboxWrapperFunctionName(string name);
			void setSandboxCode(string code);

			void registerFunction(LuaFunction luaFunction, string functionName);

			void saveGame(XmlNode *rootNode);
			void loadGame(const XmlNode *rootNode);

		private:
			string errorToString(int errorCode);
		};

		// =====================================================
		//	class LuaArguments
		// =====================================================

		class LuaArguments {
		private:
			lua_State *luaState;
			int returnCount;

		public:
			LuaArguments(lua_State *luaState);

			int getInt(int argumentIndex) const;
			string getString(int argumentIndex) const;
			void * getGenericData(int argumentIndex) const;
			Vec2i getVec2i(int argumentIndex) const;
			Vec4i getVec4i(int argumentIndex) const;

			float getFloat(int argumentIndex) const;
			Vec2f getVec2f(int argumentIndex) const;
			Vec3f getVec3f(int argumentIndex) const;
			Vec4f getVec4f(int argumentIndex) const;

			int getReturnCount() const {
				return returnCount;
			}

			void returnInt(int value);
			void returnFloat(float value);
			void returnString(const string &value);
			void returnVec2i(const Vec2i &value);
			void returnVec4i(const Vec4i &value);
			void returnVectorInt(const vector<int> &value);

		private:

			void throwLuaError(const string &message) const;
			string getStackText() const;
		};

	}
} //end namespace

#endif
