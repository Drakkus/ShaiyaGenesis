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
	this->info_file.open(this->message_builder.str(), std::ios::out | std::ios::app);

	// Clear the name builder
	this->message_builder.str(std::string());

	// Define the error log file name
	this->message_builder << log_directory << "error.log";

	// Open the error file
	this->error_file.open(this->message_builder.str(), std::ios::out | std::ios::app);

	// Clear the message builder
	this->message_builder.str(std::string());

	// Write a few newlines to the log files
	this->info_file << "#### Initialising ###" << std::endl << std::endl;
	this->error_file << "#### Initialising ###" << std::endl << std::endl;

	// The banner text
	const char* banner =
		"\n########################################\n"
		"#   _____                      _       #\n"
		"#  / ____|                    (_)      #\n"
		"# | |  __  ___ _ __   ___  ___ _ ___   #\n"
		"# | | |_ |/ _ \\ '_ \\ / _ \\/ __| / __|  #\n"
		"# | |__| |  __/ | | |  __/\\__ \\ \\__ \\  #\n"
		"#  \\_____|\\___|_| |_|\\___||___/_|___/  #\n"
		"#                                      #\n"
		"########################################\n";

	// Print the banner
	info(banner);
}

/**
* Logs an error message to both the console, and the log file specified.
*
* @param message
*		The message to write
*/
Genesis::Common::Logging::Logger* Genesis::Common::Logging::Logger::error(const char* message)
{

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
Genesis::Common::Logging::Logger* Genesis::Common::Logging::Logger::info(const char* message)
{

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