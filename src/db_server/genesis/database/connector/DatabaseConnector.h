#ifndef GENESIS_DATABASE_CONNECTOR_DATABASECONNECTOR_H
#define GENESIS_DATABASE_CONNECTOR_DATABASECONNECTOR_H

#include <mysql/mysql.h>

namespace Genesis::Database::Connector {
	class DatabaseConnector {

		public:
			bool connect();

		private:
			MYSQL* connection;
	};
}
#endif