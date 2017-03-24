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
#ifndef GENESIS_COMMON_NETWORKING_GENESISSERVER_H
#define GENESIS_COMMON_NETWORKING_GENESISSERVER_H

#include <vector>
#include <functional>
#include <boost/asio.hpp>
#include "session/ServerSession.h"

#define MAX_PACKET_LENGTH 1024

// Forward declaration of the ServerSession class
//namespace Genesis::Common::Networking::Server::Session { class ServerSession; }

/**
 * A generic server class, which accepts incoming connections and networking events.
 */
namespace Genesis::Common::Networking::Server {
	class GenesisServer {

		public:

			// The constructor, which takes an io_service and port as a parameter, and then constructs
			// the instances, and calls the bind() function.
			GenesisServer(boost::asio::io_service& io_service, unsigned short port) : io_service(io_service), acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::tcp::v4(), port)) {}

			/**
			 * Binds the server instance to a specified port
			*/
			bool bind(unsigned short port);

			/**
			 * Defines the function to be called whenever a new connection is made
			 *
			 * @param connect_function
			 *		The function to call
			 */
			void on_connect(std::function<void(Genesis::Common::Networking::Server::Session::ServerSession*)> connect_function) {
				this->connect_function = connect_function;
			}

			/**
			 * Defines the function to be called whenever a new packet is received
			 *
			 * @param receive_function
			 *		The function to call
			 */
			void on_receive(std::function<bool(Genesis::Common::Networking::Server::Session::ServerSession*, uint8_t*, unsigned int)> receive_function) {
				this->receive_function = receive_function;
			}

			/**
			 * Defines the function to be called whenever a packet to sent to a connection
			 *
			 * @param send_function
			 *		The function to call
			 */
			void on_send(std::function<void(char*)> send_function) {
				this->send_function = send_function;
			}

			/**
			 * Defines the function to be called whenever a connection is terminated
			 *
			 * @param terminate_function
			 *		The function to call
			 */
			void on_terminate(std::function<void(Genesis::Common::Networking::Server::Session::ServerSession*)> terminate_function) {
				this->terminate_function = terminate_function;
			}

		private:

			// The tcp acceptor instance
			boost::asio::ip::tcp::acceptor acceptor;

			// The io service being used
			boost::asio::io_service &io_service;

			// The on_connect lambda function, which is called whenever a new connection is made to the server
			std::function<void(Genesis::Common::Networking::Server::Session::ServerSession*)> connect_function;

			// The on_receive lambda function, which is called whenever a new packet is received
			std::function<bool(Genesis::Common::Networking::Server::Session::ServerSession*, unsigned char*, unsigned int)> receive_function;

			// The on_send lambda function, which is called whenever a packet is sent
			std::function<void(char*)> send_function;

			// The on_terminate lambda function, which is called whenever a connection is terminated
			std::function<void(Genesis::Common::Networking::Server::Session::ServerSession*)> terminate_function;

			// Begins accepting incoming connections
			void begin_accept();

			void handle_accept(Genesis::Common::Networking::Server::Session::ServerSession *session, const boost::system::error_code &error);

			void handle_read(Genesis::Common::Networking::Server::Session::ServerSession* session, unsigned char* data, const boost::system::error_code &error, unsigned int bytes_read);

	};
}
#endif