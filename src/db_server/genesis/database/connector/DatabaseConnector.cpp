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
#include "DatabaseConnector.h"
#include <genesis/common/configuration/ConfigManager.h>
#include <iostream>
#include <string>
#include <sstream>

bool Genesis::Database::Connector::DatabaseConnector::connect() {

	// Define the driver instance
	this->driver = get_driver_instance();

	// The connection instance
	auto connection = this->get_connection();

	// If the connection is valid
	bool valid = connection->isValid();

	// Delete the connection instance
	delete connection;

	// Return the status of the connection
	return valid;
}

sql::Connection* Genesis::Database::Connector::DatabaseConnector::get_connection() {
	
	// The SQL details
	auto server = config_manager->get_value_or_default<std::string>("SqlHost", "127.0.0.1");
	auto port = config_manager->get_value_or_default<unsigned short>("SqlPort", 3306);
	auto user = config_manager->get_value_or_default<std::string>("SqlUser", "root");
	auto password = config_manager->get_value_or_default<std::string>("SqlPassword", "password");

	// The stringstream
	std::stringstream stream;

	// Add the protocl
	stream << "tcp://";

	// Add the ip address
	stream << server;

	// Add the delimiter
	stream << ":";

	// Add the port
	stream << port;

	// Create a new connection
	auto connection = driver->connect(stream.str(), user, password);

	// The option
	bool client_multi_statements = true;

	// Set the client options
	connection->setClientOption("CLIENT_MULTI_STATEMENTS", &client_multi_statements);

	// Connect to the database
	return connection;
}
