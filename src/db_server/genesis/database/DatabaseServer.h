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
#ifndef GENESIS_DATABASE_DATABASESERVER_H
#define GENESIS_DATABASE_DATABASESERVER_H

#include <genesis/database/io/IoServer.h>
#include <genesis/database/connector/DatabaseConnector.h>

/**
 * The database server singleton, which listens for incoming connections by
 * the authentication and game servers, and connects to the database and retrieves
 * data requested.
 */
namespace Genesis::Database {
	class DatabaseServer {

		public:

			// Gets the singleton instance for this database server
			static DatabaseServer* get_instance() {
				static DatabaseServer instance;
				return &instance;
			}

			// Initialise the database server
			void init();

			// Get the database connector instance
			Genesis::Database::Connector::DatabaseConnector* get_connector() {
				return connector;
			}
			
		private:

			// The database connector instance
			Genesis::Database::Connector::DatabaseConnector* connector;
			
			// The IoServer instance
			Genesis::Database::Io::IoServer* io_server;
	};
}
#endif