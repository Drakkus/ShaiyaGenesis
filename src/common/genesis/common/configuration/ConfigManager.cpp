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
#include "ConfigManager.h"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>

/**
 * Attempts to parse a configuration file.
 *
 * @param file_path
 *		The path to the configuration file
 *
 * @param error_message
 *		A reference to a string that will contain the error message, if parsing fails
 *
 * @returns
 *		True if the file was parsed successfully, false if it failed and an error should be displayed.
 */
bool Genesis::Common::Configuration::ConfigManager::parse_file(std::string file_path, std::string &error_message) {

	// Check if the file exists
	if (!boost::filesystem::exists(file_path)) {
		error_message = "File doesn't exist!";
		return false;
	}

	// Attempt to parse the file
	try {

		// The full property tree
		boost::property_tree::ptree full_tree;

		// Read the configuration file
		boost::property_tree::ini_parser::read_ini(file_path, full_tree);

		// If the tree is empty, return an error
		if (full_tree.empty()) {
			error_message = "Configuration file is empty!";
			return false;
		}

		// Skip the section and get direct property access
		this->config = full_tree.begin()->second;

	// Catch any errors thrown by the parser
	} catch (boost::property_tree::ini_parser::ini_parser_error const &e) {
		if (e.line() == 0)
			error_message = e.message() + " (" + e.filename() + ")";
		else
			error_message = e.message() + " (" + e.filename() + ":" + std::to_string(e.line()) + ")";
		return false;
	}

	return true;
}