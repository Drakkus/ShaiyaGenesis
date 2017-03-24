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
#ifndef GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_AUTH_AUTHRESPONSE_H
#define GENESIS_COMMON_DATABASE_DATABASE_STRUCTS_AUTH_AUTHRESPONSE_H

/**
 * This namespace will contain all the database structures, used by the servers.
 * This will allow us to easily convert byte streams between the servers to a structure,
 * through static casting.
 */
namespace Genesis::Common::Database::Structs::Auth {

	// Represents the response to an {@code Auth_AuthRequest}
	struct AuthResponse {

		// The user id
		unsigned int user_id;

		// The status of the user (result of authentication request, ie valid, banned, invalid password)
		unsigned char status;

		// The privilege level of the user (ie staff member values, Game Sage, Game Master, Administrator)
		unsigned char privilege_level;

		// The session keys, used for identify the user
		unsigned char identity_keys[16] = {0};
	};


}
#endif