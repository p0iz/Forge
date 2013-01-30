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
 * Copyright 2012 Tommi Martela
 *
 */

#pragma once

#include <fstream>
#include <iostream>

namespace Forge { namespace Log {

class LogStream
{
public:
	LogStream(std::ostream& output, const char* file);

	template <typename MessageType>
	LogStream& operator<<(MessageType message);

	bool openLogFile(const char* newFile);
private:
	const char* mFileName;
	std::ofstream mFileStream;
	std::ostream& mOutputStream;
};

class LogStreamHandler
{
public:
	LogStreamHandler(std::ostream& output, const char* file);

	bool openLogFile(const char* newFile);

	template <typename MessageType>
	LogStream& operator<<(MessageType message);

private:
	static std::string timestamp();
	LogStream mStream;
};

template <typename MessageType>
LogStream& LogStream::operator<<(MessageType logMessage)
{
	if (!mFileStream.is_open())
		openLogFile(mFileName);

	if (mFileStream.good())
		mFileStream << logMessage;

	mOutputStream << logMessage;
	return *this;
}

template <typename MessageType>
LogStream& LogStreamHandler::operator<<(MessageType message)
{
	return mStream << timestamp() << message;
}

static LogStreamHandler info(std::cout, "./forge.log");
static LogStreamHandler error(std::cerr, "./forge.err");

}}
