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
#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

/**
 * Initialises the logger instance with a specific log directory, and opens the log files
 * for writing.
 */
void Genesis::Common::Logging::Logger::initialise(std::string log_directory) {

	// Define the information log file name
	this->message_builder << log_directory << "info.log";

	// Open the information file
	this->info_file.open(this->message_builder.str(), std::ios::out);

	// Clear the name builder
	this->message_builder.str(std::string());

	// Define the error log file name
	this->message_builder << log_directory << "error.log";

	// Open the error file
	this->error_file.open(this->message_builder.str(), std::ios::out);

	// Clear the message builder
	this->message_builder.str(std::string());

	// Write a few newlines to the log files
	this->info_file << "#### Initialising ###" << std::endl << std::endl;
	this->error_file << "#### Initialising ###" << std::endl << std::endl;

	// The banner text
	const char* banner = "\n\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\n\x23\x20\x20\x20\x5f\x5f\x5f\x5f\x5f\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x5f\x20\x20\x20\x20\x20\x20\x20\x23\n\x23\x20\x20\x2f\x20\x5f\x5f\x5f\x5f\x7c\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x28\x5f\x29\x20\x20\x20\x20\x20\x20\x23\n\x23\x20\x7c\x20\x7c\x20\x20\x5f\x5f\x20\x20\x5f\x5f\x5f\x20\x5f\x20\x5f\x5f\x20\x20\x20\x5f\x5f\x5f\x20\x20\x5f\x5f\x5f\x20\x5f\x20\x5f\x5f\x5f\x20\x20\x20\x23\n\x23\x20\x7c\x20\x7c\x20\x7c\x5f\x20\x7c\x2f\x20\x5f\x20\x5c\x20\x27\x5f\x20\x5c\x20\x2f\x20\x5f\x20\x5c\x2f\x20\x5f\x5f\x7c\x20\x2f\x20\x5f\x5f\x7c\x20\x20\x23\n\x23\x20\x7c\x20\x7c\x5f\x5f\x7c\x20\x7c\x20\x20\x5f\x5f\x2f\x20\x7c\x20\x7c\x20\x7c\x20\x20\x5f\x5f\x2f\x5c\x5f\x5f\x20\x5c\x20\x5c\x5f\x5f\x20\x5c\x20\x20\x23\n\x23\x20\x20\x5c\x5f\x5f\x5f\x5f\x5f\x7c\x5c\x5f\x5f\x5f\x7c\x5f\x7c\x20\x7c\x5f\x7c\x5c\x5f\x5f\x5f\x7c\x7c\x5f\x5f\x5f\x2f\x5f\x7c\x5f\x5f\x5f\x2f\x20\x20\x23\n\x23\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x23\n\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\x23\n";

	// Print the banner
	info(banner);
}

/**
* Logs an error message to both the console, and the log file specified.
*
* @param message
*		The message to write
*/
Genesis::Common::Logging::Logger* Genesis::Common::Logging::Logger::error(const char* message) {

	// Clear the message builder
	this->message_builder.str(std::string());

	// Build a new message
	this->message_builder << "[ERROR][" << get_current_time() << "] " << message << std::endl;

	// Write the message to the console
	std::cout << this->message_builder.str();

	// Write the message to the error log
	this->error_file << this->message_builder.str();

	// Return the logger instance
	return this;
}

/**
 * Logs an information message to both the console, and the log file specified.
 *
 * @param message
 *		The message to write
 */
Genesis::Common::Logging::Logger* Genesis::Common::Logging::Logger::info(const char* message) {

	// Clear the message builder
	this->message_builder.str(std::string());

	// Build a new message
	this->message_builder << "[INFO][" << get_current_time() << "] " << message << std::endl;

	// Write the message to the console
	std::cout << this->message_builder.str();

	// Write the message to the info log
	this->info_file << this->message_builder.str();

	// Return the logger instance
	return this;
}

/**
 * Returns the current time, in a formatted string.
 *
 * @returns
 *		The current time
 */
std::string Genesis::Common::Logging::Logger::get_current_time() {
	std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
	time_t t = std::chrono::system_clock::to_time_t(tp);
	const char * tc = ctime(&t);
	std::string str = std::string{ tc };
	str.pop_back();
	return str;
}