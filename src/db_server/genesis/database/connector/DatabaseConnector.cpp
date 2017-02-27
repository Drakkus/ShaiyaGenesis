#include "DatabaseConnector.h"
#include <genesis/common/configuration/ConfigManager.h>
#include <iostream>
#include <string>

bool Genesis::Database::Connector::DatabaseConnector::connect() {

	// The SQL details
	auto server = config_manager->get_value_or_default<std::string>("SqlHost", "127.0.0.1").c_str();
	auto user = config_manager->get_value_or_default<std::string>("SqlUser", "root").c_str();
	auto password = config_manager->get_value_or_default<std::string>("SqlPassword", "password").c_str();

	// Create a new connection
	this->driver = get_driver_instance();
	this->connection = driver->connect("tcp://127.0.0.1:3306", user, password);

	// Connect to the database
	return this->connection->isValid();
}