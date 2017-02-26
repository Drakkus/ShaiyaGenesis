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

			/**
			 * Gets the socket instance used by this session
			 *
			 * @returns
			 *		The socket
			 */
			boost::asio::ip::tcp::socket &get_socket() { 
				return this->socket;
			}

			/**
			 * Gets the io service instance that this socket is using
			 *
			 * @returns
			 *		The io service
			 */
			boost::asio::io_service &get_ioservice() { 
				return this->socket.get_io_service();
			}

			/**
			 * Gets the remote address that this session is connecting from
			 *
			 * @returns
			 *		The remote address
			 */
			std::string get_remote_address() { 
				return this->socket.remote_endpoint().address().to_string();
			}

			/**
			 * Closes the socket instance
			 */
			void close() {
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
			void write(Genesis::Common::Networking::Packets::Packet* packet) {

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

				// Write the data
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

			unsigned char* get_buffer() { 
				return data;
			}

		private:

			// The socket connection instance
			boost::asio::ip::tcp::socket socket;

			// The array that the session will receive data to
			unsigned char data[1024];


	};
}
#endif