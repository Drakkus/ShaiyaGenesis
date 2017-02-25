#include "DatabaseConnector.h"
#include <genesis/common/configuration/ConfigManager.h>
#include <iostream>
#include <string>

bool Genesis::Database::Connector::DatabaseConnector::connect() {

	// The SQL details
	auto server = config_manager->get_value_or_default<std::string>("SqlHost", "127.0.0.1").c_str();
	auto user = config_manager->get_value_or_default<std::string>("SqlUser", "root").c_str();
	auto password = config_manager->get_value_or_default<std::string>("SqlPassword", "password").c_str();

	// Initialise the MySQL connection using the C API
	this->connection = mysql_init(NULL);

	// Connect to the database
	return mysql_real_connect(this->connection, server, user, password, "genesis_userdata", 0, NULL, 0);
}