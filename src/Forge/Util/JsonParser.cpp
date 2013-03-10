/* This file is part of Forge.
 *
 * Forge is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Forge is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with Forge.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Copyright 2013 Tommi Martela
 *
 */

#include "JsonParser.h"

#include "HashUtils.h"

#include <cassert>

#include <iostream>
#include <sstream>
#include <fstream>

namespace Forge {

JsonParser::JsonParser(const char *filename) : mFilename(filename) {
}

bool JsonParser::parse() {
	resetParser();

	std::ifstream inputFile;
	inputFile.open(mFilename);

	while (inputFile.good() && !parseError)
	{
		parse(inputFile.get());
	}

	if (!parseError)
		parseError = (!containerStack.empty() || read_to_key);

	return !parseError;
}

const JsonObject& JsonParser::getRootObject() const
{
	return root_object;
}

void JsonParser::parse(char read_char)
{
	// Parse keys and values
	if (in_string && read_char != '"') {
		if (read_to_key) {
			key.push_back(read_char);
		} else {
			value.push_back(read_char);
		}
		return;
	}

	switch (read_char)
	{
	case '{':
		if (!containerStack.empty() && containerStack.back() == OBJECT) {
			previous_object_key.push_back(key);
		}
		key.clear();
		object_stack.push_back(JsonObject());
		containerStack.push_back(OBJECT);
		read_to_key = true;
		break;
	case '}':
		if (containerStack.back() == OBJECT) {
			read_to_key = false;
			JsonObject parsed_object = object_stack.back(); // Get the closed object
			object_stack.pop_back();
			if (!object_stack.empty()) {
				// The object is a value in a containing object
				JsonValue value;
				value.object.reset(new JsonObject(parsed_object));
				key = previous_object_key.back();
				previous_object_key.pop_back();
				object_stack.back().key_values[key] = value;
			} else {
				// We are at root so break out and hope that parsing ends
				root_object = parsed_object;
			}
			containerStack.pop_back();
		} else {
			// parse error
			parseError = true;
		}
		break;
	case '[':
		containerStack.push_back(ARRAY);
		break;
	case ']':
		if (containerStack.back() == ARRAY) {
			containerStack.pop_back();
		} else {
			// parse error
			parseError = true;
		}
		break;
	case '\n':
		++current_line;
		break;
	case ',':
		// new element in object or array
		object_stack.back().key_values[key].value.push_back(value);
		if (containerStack.back() == OBJECT) {
			// Add a new key, old key-value is added to the map
			key.clear();
			read_to_key = true;
		}
		value.clear();
		break;
	case ':' :
		if (containerStack.back() == OBJECT) {
			read_to_key = false;
		} else {
			parseError = true;
		}
		break;
	case '"':
		in_string = !in_string;
		break;
	default:
		if (!isspace(read_char) && !read_to_key) {
			value.push_back(read_char);
		}
		break;
	}
}

void JsonParser::resetParser()
{
	containerStack.clear();
	object_stack.clear();
	previous_object_key.clear();
	root_object = JsonObject();
	key.clear();
	value.clear();
	read_to_key = false;
	parseError = false;
	current_line = 1;
	in_string = false;
}

int JsonParser::getLastParsedLine() const
{
	return current_line;
}

void JsonObject::printContents() const
{
	printObject(*this, 0);
}

void JsonObject::printObject(const JsonObject &object, const int indentation) const
{

	for (std::map<std::string, JsonValue>::const_reference key_value : object.key_values)
	{
		for (int i=0; i < indentation; ++i)
			std::cout << "\t";
		std::cout << key_value.first << " : ";
		if (key_value.second.object) {
			std::cout << "\n";
			printObject(*key_value.second.object, indentation+1);
		} else {
			for (std::string item : key_value.second.value) {
				std::cout << item << " ";
			}
			std::cout << "\n";
		}
	}
}

bool JsonObject::hasValue(const StringValueMap::key_type& key) const
{
	return key_values.count(key) > 0;
}

}
