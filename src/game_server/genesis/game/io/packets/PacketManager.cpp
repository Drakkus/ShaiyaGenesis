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
#include <genesis/game/io/packets/PacketManager.h>
#include <genesis/game/io/packets/PacketHandler.h>
#include <genesis/game/io/packets/impl/Handlers.h>
#include <genesis/common/packets/Opcodes.h>

// The opcodes namespace
namespace Opcodes = Genesis::Common::Packets::Opcodes;

/**
 * The {@code PacketManager} constructor, which is used to pre-define the packet handlers
 * for the opcodes used by the Shaiya Genesis authentication server.
 */
Genesis::Game::Io::Packets::PacketManager::PacketManager() {

	// The default packet handler
	this->handlers[0] = new Genesis::Game::Io::Packets::Impl::DefaultPacketHandler();

	// Define the packet handlers
	this->handlers[Opcodes::GAME_HANDSHAKE] = new Genesis::Game::Io::Packets::Impl::GameHandshakePacketHandler();
	this->handlers[Opcodes::AVAILABLE_CHARACTER_NAME] = new Genesis::Game::Io::Packets::Impl::CheckAvailableNamePacketHandler();
	this->handlers[Opcodes::CREATE_CHARACTER] = new Genesis::Game::Io::Packets::Impl::CreateCharacterPacketHandler();
	this->handlers[Opcodes::ACCOUNT_FACTION] = new Genesis::Game::Io::Packets::Impl::SelectFactionPacketHandler();
	this->handlers[Opcodes::DELETE_CHARACTER] = new Genesis::Game::Io::Packets::Impl::DeleteCharacterPacketHandler();
	this->handlers[Opcodes::RESTORE_CHARACTER] = new Genesis::Game::Io::Packets::Impl::RestoreCharacterPacketHandler();
	this->handlers[Opcodes::CHARACTER_SELECTION] = new Genesis::Game::Io::Packets::Impl::SelectCharacterPacketHandler();
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
Genesis::Game::Io::Packets::PacketHandler* Genesis::Game::Io::Packets::PacketManager::get_handler(unsigned short opcode) {

	// The number of key instances for the opcode
	int count = this->handlers.count(opcode);

	// Return the handler
	return (count >= 1 ? this->handlers[opcode] : this->handlers[0]);
}