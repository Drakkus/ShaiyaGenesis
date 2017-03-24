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
#ifndef GENESIS_DATABASE_IO_IOSERVER_H
#define GENESIS_DATABASE_IO_IOSERVER_H

#include <genesis/database/io/packets/PacketManager.h>
#include <genesis/database/io/packets/PacketHandler.h>

#include <string>

// Forward declaration of the ServerSession class
namespace Genesis::Common::Networking::Server::Session { class ServerSession; }

/**
 * An IoServer which uses the {@link Genesis::Common::Networking::Server::GenesisServer} class to bind
 * to a socket, and listen for incoming network events.
 */
namespace Genesis::Database::Io {
	class IoServer {

		public:

			// Initialise the IoServer on a specified address and port
			bool initialise(unsigned short port);

		private:

			// The packet manager instance
			Genesis::Database::Io::Packets::PacketManager* packet_manager = new Genesis::Database::Io::Packets::PacketManager();

			// Called whenever a new connection is made
			void on_connect(Genesis::Common::Networking::Server::Session::ServerSession* session);

			// Called whenever a packet is received
			bool on_receive(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned char* data, unsigned int bytes_read);

			// Called whenever a packet is sent
			void on_send(char* name);

			// Called whenever a connection is terminated
			void on_terminate(Genesis::Common::Networking::Server::Session::ServerSession*);
	};
}
#endif