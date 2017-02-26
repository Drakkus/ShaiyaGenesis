#include <genesis/database/io/packets/PacketManager.h>
#include <genesis/database/io/packets/PacketHandler.h>
#include <genesis/database/io/packets/impl/Handlers.h>
#include <genesis/common/database/Opcodes.h>

// The opcodes namespace
namespace Opcodes = Genesis::Common::Database::Opcodes;

/**
 * The {@code PacketManager} constructor, which is used to pre-define the packet handlers
 * for the opcodes used by the Shaiya Genesis database server.
 */
Genesis::Database::Io::Packets::PacketManager::PacketManager() {

	// The default packet handler
	this->handlers[0] = new Genesis::Database::Io::Packets::Impl::DefaultPacketHandler();

	// Define the database server packet handlers
	this->handlers[Opcodes::USER_AUTH_REQUEST] = new Genesis::Database::Io::Packets::Impl::UserAuthRequestHandler();
}

/**
 * Gets the handler assigned to a specific opcode
 *
 * @param opcode
 * 		The opcode
 *
 * @returns
 *		The handler if found. If not, the {@link DefaultPacketHandler} instance is returned
 */
Genesis::Database::Io::Packets::PacketHandler* Genesis::Database::Io::Packets::PacketManager::get_handler(unsigned short opcode) {

	// The number of key instances for the opcode
	int count = this->handlers.count(opcode);

	// Return the handler
	return (count >= 1 ? this->handlers[opcode] : this->handlers[0]);
}