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
#include "ServerSession.h"

// Use the session namespace
using namespace Genesis::Common::Networking::Server::Session;

/**
 * Gets the socket instance used for this {@code Session}
 *
 * @returns
 *		The socket
 */
boost::asio::ip::tcp::socket &ServerSession::get_socket() { 
	return this->socket;
}

/**
 * Gets the io service instance that this socket is using
 *
 * @returns
 *		The io service
 */
boost::asio::io_service &ServerSession::get_ioservice() { 
	return this->socket.get_io_service();
}

/**
 * Gets the remote address that this session is connecting from
 *
 * @returns
 *		The remote address
 */
std::string ServerSession::get_remote_address() { 
	return this->socket.remote_endpoint().address().to_string();
}

/**
 * Closes the socket instance
 */
void ServerSession::close() {
	if (this->get_socket().is_open()) {
		this->get_socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		this->get_socket().close();
	}
}

/**
 * Writes a packet to this session's socket
 *
 * @param packet
 *		The packet instance to write
 */
void ServerSession::write(Genesis::Common::Networking::Packets::Packet* packet) {

	// The array to write to
	unsigned char* data = new unsigned char[packet->length];

	// Write the length
	data[0] = (packet->length);
	data[1] = (packet->length >> 8);

	// Write the opcode
	data[2] = (packet->opcode);
	data[3] = (packet->opcode >> 8);

	// Write the data
	for (int i = 0; i < packet->payload.size(); i++) {
		data[4 + i] = packet->payload.at(i);
	}

	// Write the data<< 
	boost::asio::async_write(this->socket, boost::asio::buffer(data, packet->length),
		[&](const boost::system::error_code& error, unsigned int bytes_written) {

			// If an error occurred, close the socket if it is still open
			if (error && this->get_socket().is_open()) {
				this->get_socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both);
				this->get_socket().close();
			}
	});
	
	// Delete the data array and packet
	delete[] data;
	delete packet;
}

void ServerSession::clear_identity_keys() {
	for (int i = 0; i < sizeof(this->identity_keys); i++)
		this->identity_keys[i] = '\0';
}

/**
 * Sets the identity keys for this session
 *
 * @param keys
 *		The keys
 */
void ServerSession::set_identity_keys(unsigned char* keys) {
	for (int i = 0; i < sizeof(this->identity_keys); i++)
		this->identity_keys[i] = keys[i];
}

/**
 * Gets the identity keys for this session
 *
 * @returns
 *		This session's identity keys
 */
unsigned char* ServerSession::get_identity_keys() {
	return this->identity_keys;
}

/**
 * Gets the packet buffer for this session
 *
 * @return
 *		This session's buffer
 */
unsigned char* ServerSession::get_buffer() { 
	return this->data;
}