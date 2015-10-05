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

#include "Log.h"

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

namespace Forge { namespace Log {

std::string LogStreamHandler::timestamp()
{
	const time_t currentTime = time(nullptr);
	char timeStampData[23];
	strftime(timeStampData, 23, "[%d.%m.%Y %H:%M:%S] ", localtime(&currentTime));
	std::string timeStampString;
	timeStampString.assign(timeStampData);
	return timeStampString;
}

LogStream::LogStream(std::ostream &output, const char* file)
	: mFileName(file), mOutputStream(output)
{
}

LogStream::~LogStream()
{
  mFileStream.close();
}

bool LogStream::openLogFile(const char *newFile)
{
	if (!mFileStream.is_open())
		mFileStream.close();
	mFileStream.open(newFile, std::ios_base::out|std::ios_base::app);
	return mFileStream.good();

}

bool LogStreamHandler::openLogFile(const char* newFile)
{
	return mStream.openLogFile(newFile);
}

LogStreamHandler::LogStreamHandler(std::ostream &output, const char *file)
  : mStream(output, file)
{
}

LogStreamHandler::~LogStreamHandler()
{
}

}}
