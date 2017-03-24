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
#ifndef GENESIS_DATABASE_IO_PACKETS_IMPL_USERAUTHREQUESTHANDLER_H
#define GENESIS_DATABASE_IO_PACKETS_IMPL_USERAUTHREQUESTHANDLER_H

#include <genesis/database/io/packets/PacketHandler.h>
#include <genesis/database/DatabaseServer.h>
#include <genesis/common/networking/packets/PacketBuilder.h>

#include <genesis/common/database/structs/auth/AuthRequest.h>
#include <genesis/common/database/structs/auth/AuthResponse.h>

#include <iostream>

namespace Genesis::Database::Io::Packets::Impl {
	class UserAuthRequestHandler : public PacketHandler {

		/**
		 * Handles an undefined packet
		 *
		 * @param session
		 *		The session instance
		 *
		 * @param length
		 *		The length of the packet
		 *
		 * @param opcode
		 *		The opcode of the incoming packet
		 *
		 * @param data
		 *		The packet data
		 */
		bool handle(Genesis::Common::Networking::Server::Session::ServerSession* session, 
				unsigned int length, unsigned short opcode, unsigned int request_id, unsigned char* data) override {

			// The auth request instance
			Genesis::Common::Database::Structs::Auth::AuthRequest request;

			// Copy the data
			memcpy(&request, data, sizeof(request));
			
			// The MySQL connection
			auto connection = Genesis::Database::DatabaseServer::get_instance()->get_connector()->get_connection();

			// The statement and result instances
			auto statement = connection->createStatement();
			
			// The prepared statement
			std::auto_ptr<sql::PreparedStatement> prepared;

			// The result set
			std::auto_ptr<sql::ResultSet> result;

			// Reset the prepared statement
			prepared.reset(connection->prepareStatement("CALL genesis_userdata.validate_login_request(?, ?, ?, @result, @user_id, @privilege_level, @identity_keys)"));

			// The username, password and ip address, as strings
			std::string username((char*) request.username);
			std::string password((char*) request.password);
			std::string ip_address((char*) request.ip_address);

			// Define the username, password, and ip address
			prepared->setString(1, sql::SQLString(username.c_str()));
			prepared->setString(2, sql::SQLString(password.c_str()));
			prepared->setString(3, sql::SQLString(ip_address.c_str()));

			// Execute the prepared statement
			prepared->execute();

			// Retrieve the results
			result.reset(statement->executeQuery("SELECT @result as $result, @user_id as $user_id, @privilege_level as $privilege_level, @identity_keys as $identity_keys"));

			// Loop through the results
			if (result->next()) {
				
				// The auth response stucture
				Genesis::Common::Database::Structs::Auth::AuthResponse auth_response;

				// The values
				int user_id = result->getInt("$user_id");
				unsigned char status = (unsigned char) result->getInt("$result");
				unsigned char privilege_level = (unsigned char) result->getInt("$privilege_level");
				std::string id_keys = (std::string) result->getString("$identity_keys");

				// Define the values
				auth_response.user_id = user_id;
				auth_response.status = status;
				auth_response.privilege_level = privilege_level;

				// The identity keys
				auto keys = id_keys.c_str();

				// Define the identity keys
				std::copy(keys, keys + sizeof(auth_response.identity_keys), auth_response.identity_keys);
				
				// The byte array
				unsigned char struct_array[sizeof(auth_response)];
				memcpy(struct_array, &auth_response, sizeof(auth_response));

				// The packet builder instance
				auto bldr = new Genesis::Common::Networking::Packets::PacketBuilder(opcode);

				// Write the request id
				bldr->write_int(request_id);

				// Write the struct array
				bldr->write_bytes(struct_array, sizeof(struct_array));

				// Write the packet
				session->write(bldr->to_packet());

				// Delete the packet builder
				delete bldr;
			}

			// Close the statement
			statement->close();

			// Delete the statement
			delete statement;

			// Delete the connection
			delete connection;
			
			// Return true
			return true;
		}
	};
}
#endif