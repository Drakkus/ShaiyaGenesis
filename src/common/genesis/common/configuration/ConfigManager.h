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
#ifndef GENESIS_COMMON_CONFIGURATION_CONFIGMANAGER_H
#define GENESIS_COMMON_CONFIGURATION_CONFIGMANAGER_H

#include <string>
#include <mutex>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

/**
 * A utility class used for parsing a configuration file, and then retrieving the various values.
 */
namespace Genesis::Common::Configuration {
	class ConfigManager {

		public:

			// Gets the singleton instance for the logger
			static ConfigManager* get_instance() {
				static ConfigManager instance;
				return &instance;
			}

			// Parses a configuration file
			bool parse_file(std::string file, std::string &error_message);

			// Gets a value of a specified type, or the default value
			template<typename T>
			T get_value_or_default(std::string const& name, T default_value) const {

				// Attempt to get the value
				try {

					// The value
					T value = (T) this->config.get<T>(boost::property_tree::ptree::path_type(name, '/'));
					
					// If the value is a string
					if (std::is_same<T, std::string>::value) {
						
						// The string value
						std::string* str_val = (std::string*) &value;
						
						// Erase all quotes in the string
						str_val->erase(std::remove(str_val->begin(), str_val->end(), '"'), str_val->end());
					}
				
					// Return the value
					return value;

				} catch (boost::property_tree::ptree_bad_path &e) {
					std::cout << e.what() << std::endl;
				} catch (boost::property_tree::ptree_bad_data &e) {
					std::cout << e.what() << std::endl;
				}

				// If any errors occurred, return the default value
				return default_value;
			}

		private:

			// The config property tree
			boost::property_tree::ptree config;

			// The configuration lock
			std::mutex config_lock;
	};
}

// A macro for easily obtaining the configuration manager instance
#define config_manager Genesis::Common::Configuration::ConfigManager::get_instance()

#endif
