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
#ifndef GENESIS_COMMON_LOGGING_LOGGER_H
#define GENESIS_COMMON_LOGGING_LOGGER_H

#include <string>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

/**
 * A utility class used for logging information and/or error messages to the console,
 * and an external log file. This logger is initiliased with the log paths when a server
 * starts up, and is used as a singleton throughout the application.
 */
namespace Genesis::Common::Logging {
	class Logger {

		public:

			// Gets the singleton instance for the logger
			static Logger* get_instance() {
				static Logger instance;
				return &instance;
			}

			// Initialises the logger instance by specifying a logger directory
			void initialise(std::string log_directory);

			// Logs an information message
			Logger* info(const char* message);
			Logger* info(std::string message) { return this->info(message.c_str()); }
			Logger* info(const char* message, std::initializer_list<const char*> args) {
				
				// The message
				auto boost_msg = boost::format(message);

				// Loop through the arguments
				for (auto arg : args) {

					// Define the message
					boost_msg = boost_msg % arg;

				}
				
				// Write the info message
				return info(boost::str(boost_msg));
			
			}

			// Logs an error message
			Logger* error(const char* message);
			Logger* error(std::string message) { return this->error(message.c_str()); }
			Logger* error(const char* message, std::initializer_list<const char*> args) {
				
				// The message
				auto boost_msg = boost::format(message);

				// Loop through the arguments
				for (auto arg : args) {

					// Define the message
					boost_msg = boost_msg % arg;

				}
				
				// Write the error message
				return error(boost::str(boost_msg));
			
			}

		private:

			// The log files
			std::ofstream info_file;
			std::ofstream error_file;

			// Gets the current time
			std::string get_current_time();

			// A string stream instance for building the messages
			std::stringstream message_builder;
	};
}

// A macro for easily obtaining a logger instance
#define genesis_logger Genesis::Common::Logging::Logger::get_instance()

#endif