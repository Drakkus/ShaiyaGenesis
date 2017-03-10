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
	this->handlers[Opcodes::SERVER_LIST] = new Genesis::Database::Io::Packets::Impl::ServerListRequestHandler();
	this->handlers[Opcodes::DELETE_SESSION] = new Genesis::Database::Io::Packets::Impl::DeleteSessionRequestHandler();
	this->handlers[Opcodes::USER_GAME_CONNECT] = new Genesis::Database::Io::Packets::Impl::UserGameConnectRequestHandler();
	this->handlers[Opcodes::GAME_USER_LOAD] = new Genesis::Database::Io::Packets::Impl::GameUserLoadRequestHandler();
	this->handlers[Opcodes::CHECK_AVAILABLE_NAME] = new Genesis::Database::Io::Packets::Impl::CheckAvailableNameRequestHandler();
	this->handlers[Opcodes::CREATE_CHARACTER] = new Genesis::Database::Io::Packets::Impl::CreateCharacterRequestHandler();
	this->handlers[Opcodes::GET_CHARACTER_LIST_DATA] = new Genesis::Database::Io::Packets::Impl::CharacterScreenDataRequestHandler();
	this->handlers[Opcodes::SELECT_FACTION] = new Genesis::Database::Io::Packets::Impl::SelectFactionRequestHandler();
	this->handlers[Opcodes::DELETE_CHARACTER] = new Genesis::Database::Io::Packets::Impl::DeleteCharacterRequestHandler();
	this->handlers[Opcodes::RESTORE_CHARACTER] = new Genesis::Database::Io::Packets::Impl::RestoreCharacterRequestHandler();
	this->handlers[Opcodes::LOAD_GAME_CHARACTER] = new Genesis::Database::Io::Packets::Impl::LoadGameCharacterDataRequestHandler();
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