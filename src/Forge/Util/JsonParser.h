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

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace Forge {

struct JsonObject;

struct JsonValue
{
	std::vector<std::string> value;
	std::shared_ptr<JsonObject> object;
};

struct JsonObject
{
	void printContents() const;
	void printObject(const JsonObject& object, const int indentation) const;

	typedef std::map<std::string, JsonValue> StringValueMap;
	StringValueMap key_values;

	bool hasValue(const StringValueMap::key_type& key) const;
};

class JsonParser {
public:
	JsonParser(const char* filename);
	bool parse();
	const JsonObject& getRootObject() const;
	int getLastParsedLine() const;
private:
	void parse(char readChar);
	void resetParser();

	enum JsonContainerType {
		OBJECT,
		ARRAY
	};

	enum JsonValueType {
		STRING,
		NUMBER,
		BOOLEAN,
		NOTHING
	};

	std::vector<JsonContainerType> containerStack;
	std::vector<JsonObject> object_stack;
	std::string key, value;
	std::vector<std::string> previous_object_key;
	std::string current_value;
	JsonObject root_object;

	bool read_to_key;

	int current_line;
	bool in_string;
	int indent;

	bool parseError;

	const char* mFilename;
};

}
