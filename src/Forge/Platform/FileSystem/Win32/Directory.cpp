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

#include "../Directory.hpp"
#include "Util/Log.h"
#include <windows.h>


namespace Forge { namespace FileSystem {

Directory::Directory():
  mCurrentPath(getenv("%HOMEDRIVE%"))
{
  mCurrentPath.append(getenv("%HOMEDRIVE%"));
  Forge::Log::info << "Got default path: " << mCurrentPath << "\n";
}

std::string Directory::getCurrentWorkingDir()
{
  char currentDir[MAX_PATH] = { 0 };
  GetCurrentDirectory(MAX_PATH, currentDir);
  return currentDir;
}

bool Directory::create()
{
  if (exists())
    return false;

  return CreateDirectory(mCurrentPath.c_str(), NULL);
}

bool Directory::exists() const
{
  DWORD fileAttribute = GetFileAttributes(mCurrentPath.c_str());
  return fileAttribute == FILE_ATTRIBUTE_DIRECTORY;
}

bool Directory::contains(const std::string& name) const
{
  DWORD fileAttribute = GetFileAttributes(mCurrentPath.c_str());
  return fileAttribute == FILE_ATTRIBUTE_NORMAL;
}

bool Directory::hasSubDir(const std::string& name) const
{
  std::string subDirPath(mCurrentPath + getSeparator());
  subDirPath.append(name);
  DWORD fileAttribute = GetFileAttributes(subDirPath.c_str());
  return fileAttribute == FILE_ATTRIBUTE_DIRECTORY;
}

bool Directory::createDir(const std::string& name)
{
  return CreateDirectory((mCurrentPath + getSeparator() + name).c_str(), NULL);
}

bool Directory::createFile(const std::string& name)
{
  return CreateDirectory((mCurrentPath + getSeparator() + name).c_str(), NULL);
}

std::vector<std::string> Directory::listFiles() const
{
  std::vector<std::string> files;

  WIN32_FIND_DATA findData;

  HANDLE findHandle = FindFirstFile((mCurrentPath + "\\*").c_str(), &findData);

  if (findHandle == INVALID_HANDLE_VALUE)
  {
    return files;
  }

  do
  {
    if (findData.dwFileAttributes & FILE_ATTRIBUTE_NORMAL)
    {
      files.push_back(findData.cFileName);
    }
  }
  while (FindNextFile(findHandle, &findData) != 0);

  FindClose(findHandle);

  return files;
}

std::vector<Forge::FileSystem::Directory> Directory::listDirectories() const
{
  std::vector<Directory> directories;

  WIN32_FIND_DATA findData;

  HANDLE findHandle = FindFirstFile((mCurrentPath + "\\*").c_str(), &findData);

  if (findHandle == INVALID_HANDLE_VALUE)
  {
    return directories;
  }

  do
  {
    if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
      directories.push_back(Directory(mCurrentPath + getSeparator() + findData.cFileName));
    }
  }
  while (FindNextFile(findHandle, &findData) != 0);

  FindClose(findHandle);

  return directories;
}

constexpr char Directory::getSeparator()
{
  return '\\';
}

bool Directory::isAbsolutePath() const
{
  return mCurrentPath[1] == ':' && mCurrentPath[2] == getSeparator();
}

}}
