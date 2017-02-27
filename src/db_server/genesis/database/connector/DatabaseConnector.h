#ifndef GENESIS_DATABASE_CONNECTOR_DATABASECONNECTOR_H
#define GENESIS_DATABASE_CONNECTOR_DATABASECONNECTOR_H

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

namespace Genesis::Database::Connector {
	class DatabaseConnector {

		public:
			bool connect();
			sql::Connection* get_connection() { return connection; }
		private:
			sql::Driver* driver;
			sql::Connection* connection;
	};
}
#endif