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
			void on_receive(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned char* data, unsigned int bytes_read);

			// Called whenever a packet is sent
			void on_send(char* name);

			// Called whenever a connection is terminated
			void on_terminate(Genesis::Common::Networking::Server::Session::ServerSession*);
	};
}
#endif