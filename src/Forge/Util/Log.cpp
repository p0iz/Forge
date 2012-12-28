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

const char* Log::errorFileName = "./forge.err";
const char* Log::infoFileName = "./forge.log";

Log::Log()
{
	mInfoStream.open(infoFileName, std::ios_base::out|std::ios_base::app);
	mErrorStream.open(errorFileName, std::ios_base::out|std::ios_base::app);
}

std::string Log::timestamp()
{
	const time_t currentTime = time(nullptr);
	char timeStampData[20];
	strftime(timeStampData, 20, "[%d.%m.%Y %H:%M]", localtime(&currentTime));
	std::string timeStampString;
	timeStampString.assign(timeStampData);
	return timeStampString;
}

void Log::writeLog(std::ofstream& log, std::ostream& output, const char* message)
{
	std::stringstream logLine;
	logLine << "-=[ " << timestamp() << "]=[ " << message << " ]=-\n";
	output << logLine.str();
	log << logLine.str();
}

std::ostream& Log::info()
{
	return mInfoStream << "[ " << timestamp() << " ] ";
}

std::ostream& Log::error()
{
	return mErrorStream << "[ " << timestamp() << " ] ";
}

void Log::setInfoFile(const char* infoFileName)
{
	infoFileName = infoFileName;
}

void Log::setErrorFile(const char* errorFileName)
{
	errorFileName = errorFileName;
}
