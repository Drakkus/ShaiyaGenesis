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
#include <genesis/common/logging/Logger.h>
#include <genesis/common/configuration/ConfigManager.h>

#include <genesis/database/DatabaseServer.h>

#include <iostream>

/**
* The entry point for the Shaiya Genesis authentication server application.
*
* @param argc
*		The count of command-line arguments
*
* @param argv
*		The command-line argument values
*/
int main(int argc, char** argv) {
	
	// The configuration file path
	std::string config_path = (argc >= 2 ? argv[1] : "./config/db_server.conf");

	// The configuration error
	std::string config_error;

	// Parse the configuration file
	if (!config_manager->parse_file(config_path, config_error)) {
		printf("Failed to parse configuration file at the path: %s\nError message: %s\n", config_path.c_str(), config_error.c_str());
		return 1;
	}

	// Initialise the logger
	genesis_logger->initialise(config_manager->get_value_or_default<std::string>("LogsDirectory", "./logs/database/"));

	// Inform the user that the configuration had been parsed
	genesis_logger->info("Database server configuration has been parsed successfully!");

	// Initialise the database server
	Genesis::Database::DatabaseServer::get_instance()->init();
}