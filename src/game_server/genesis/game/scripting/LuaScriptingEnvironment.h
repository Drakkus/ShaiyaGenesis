/*
* Copyright (C) 2017 Shaiya Genesis <http://www.shaiyagenesis.com/>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:

* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#ifndef GENESIS_GAME_SCRIPTING_LUASCRIPTINGENVIRONMENT_H
#define GENESIS_GAME_SCRIPTING_LUASCRIPTINGENVIRONMENT_H

#include <genesis/common/logging/Logger.h>
#include <genesis/common/scripting/sol.hpp>

/**
 * The Lua Scripting environment instance, which is used to parse the Lua scripts, and add
 * various event listeners to be executed.
 */
namespace Genesis::Game::Scripting {
	class LuaScriptingEnvironment {

		public:

			/* Gets the singleton instance for this scripting environment */
			static LuaScriptingEnvironment* get_instance() {
				static LuaScriptingEnvironment env;
				return &env;
			}

			/* Initialise the scripting environment */
			void init();
			
		private:

			/* The lua state instance */
			sol::state state;

			/* Load all the scripts in the specific directory */
			void load_all_scripts(std::string, sol::table);

			/* Loads a single script into the Lua state instance */
			void load_script(sol::table, std::string);
	};
}

/* A macro for getting the singleton instance */
#define scripting_env Genesis::Game::Scripting::LuaScriptingEnvironment::get_instance()

#endif