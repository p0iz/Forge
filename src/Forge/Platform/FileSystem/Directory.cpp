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

#include "Directory.hpp"

// Common directory management functions

namespace Forge { namespace FileSystem {

Directory::Directory(std::string const& path):
  mCurrentPath(path)
{
  if (*path.rbegin() == SEPARATOR)
  {
    mCurrentPath.pop_back();
  }
  convertToAbsolutePath();
}

Directory::Directory(Directory const& rhs):
  mCurrentPath(rhs.mCurrentPath)
{
}

Directory const& Directory::operator=(Directory const& rhs)
{
  mCurrentPath = rhs.mCurrentPath;
  return *this;
}

Directory::~Directory()
{
}

const std::string& Directory::getCurrentPath() const
{
  return mCurrentPath;
}

std::string Directory::getName() const
{
  return mCurrentPath.substr(mCurrentPath.find_last_of(SEPARATOR)+1);
}

void Directory::goUp()
{
  mCurrentPath = getParent();
}

bool Directory::cd(std::string const& dir)
{
  Directory newDir(mCurrentPath);
  std::string::size_type startIndex = 0;
  std::string::size_type endIndex = 0;
  do
  {
    endIndex = dir.find_first_of(SEPARATOR, startIndex);
    std::string nextDir = dir.substr(startIndex, endIndex - startIndex);

    if (nextDir == "..")
    {
      newDir.goUp();
    }
    else if (nextDir != "." && nextDir != "")
    {
      if (!newDir.hasSubDir(nextDir))
      {
        return false;
      }
      else
      {
        std::string newPath(newDir.getCurrentPath());
        newDir = Directory(newPath.append("/").append(nextDir));
      }
    }
    startIndex = endIndex+1;
  }
  while (endIndex != std::string::npos);

  mCurrentPath = newDir.getCurrentPath();

  return true;
}

void Directory::convertToAbsolutePath()
{
  if (isAbsolutePath())
    return;

  std::string currentWorkingDir(getCurrentWorkingDir());
  std::string::size_type startIndex = 0;
  std::string::size_type endIndex = 0;
  while (endIndex != std::string::npos)
  {
    endIndex = mCurrentPath.find_first_of(SEPARATOR, startIndex);
    std::string currentElement = mCurrentPath.substr(startIndex, endIndex);
    if (currentElement == "..")
    {
      // Remove one level of current working dir
      currentWorkingDir = currentWorkingDir.substr(currentWorkingDir.find_last_of('/'));
    }
    else if (currentElement != ".")
    {
      currentWorkingDir.push_back(SEPARATOR);
      currentWorkingDir.append(currentElement);
    }
    startIndex = endIndex+1;
  }
  mCurrentPath = currentWorkingDir;
}

std::string Directory::getParent() const
{
  return mCurrentPath.substr(0, mCurrentPath.find_last_of(SEPARATOR));
}

}}
