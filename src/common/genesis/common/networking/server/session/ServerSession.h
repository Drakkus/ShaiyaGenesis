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
#ifndef GENESIS_COMMON_NETWORKING_SERVER_SESSION_SERVERSESSION_H
#define GENESIS_COMMON_NETWORKING_SERVER_SESSION_SERVERSESSION_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "../../packets/Packet.h"
#include <iostream>

/**
 * Represents a session that is currently connected to a server instance.
 */
namespace Genesis::Common::Networking::Server::Session {
	class ServerSession {

		public:

			// Constructor which creates the socket from the io service instance
			ServerSession(boost::asio::io_service &io_service) : socket(io_service) {}

			// Destructor, which handles the deletion of session members
			~ServerSession() {}

			/**
			 * Gets the socket instance used by this session
			 *
			 * @returns
			 *		The socket
			 */
			boost::asio::ip::tcp::socket &get_socket();

			/**
			 * Gets the io service instance that this socket is using
			 *
			 * @returns
			 *		The io service
			 */
			boost::asio::io_service &get_ioservice();

			/**
			 * Gets the remote address that this session is connecting from
			 *
			 * @returns
			 *		The remote address
			 */
			std::string get_remote_address();

			/**
			 * Closes the socket instance
			 */
			void close();

			/**
			 * Writes a packet to this session's socket
			 *
			 * @param packet
			 *		The packet instance to write
			 */
			void write(Genesis::Common::Networking::Packets::Packet* packet);

			/**
			 * Clears the session identity keys
			 */
			void clear_identity_keys();

			/**
			 * Sets the identity keys for this session
			 *
			 * @param keys
			 *		The keys
			 */
			void set_identity_keys(unsigned char* keys);

			/**
			 * Gets the identity keys for this session
			 *
			 * @return
			 *		This session's identity keys
			 */
			unsigned char* get_identity_keys();

			/**
			 * Gets the packet buffer for this session
			 *
			 * @return
			 *		This session's buffer
			 */
			unsigned char* get_buffer();

			/**
			 * Sets the game player index for this session
			 *
			 * @param index
			 *		The index
			 */
			void set_game_index(unsigned int index) {
				this->index = index;
			}

			/**
			 * Gets the index of the game player
			 */
			unsigned int get_game_index() {
				return index;
			}

		private:

			// The socket connection instance
			boost::asio::ip::tcp::socket socket;

			// The session index (used by the game server)
			unsigned int index;

			// The identity keys for this session
			unsigned char identity_keys[16];

			// The array that the session will receive data to
			unsigned char data[1024];

	};
}
#endif