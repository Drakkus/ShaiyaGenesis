#ifndef GENESIS_DATABASE_IO_PACKETS_PACKETMANAGER_H
#define GENESIS_DATABASE_IO_PACKETS_PACKETMANAGER_H

#include <map>

// Forward declaration of the PacketHandler class
namespace Genesis::Database::Io::Packets { class PacketHandler; }

/**
 * The PacketManager class, which assigns the packet handler for each opcode.
 * This is referenced as a singleton, and is used to call the approprite handler instances
 */
namespace Genesis::Database::Io::Packets {
	class PacketManager {

		public:

			// The constructor, which initialises the handler instances
			PacketManager();

			/**
			 * Retrieves the PacketHandler for a specific opcode
			 *
			 * @param opcode
			 *		The opcode
			 *
			 * @returns
			 *		The packet handler
			 */
			Genesis::Database::Io::Packets::PacketHandler* get_handler(unsigned short opcode);
			
		private:

			// The map of opcodes to packet handlers
			std::map<unsigned short, Genesis::Database::Io::Packets::PacketHandler*> handlers;
	};
}
#endif