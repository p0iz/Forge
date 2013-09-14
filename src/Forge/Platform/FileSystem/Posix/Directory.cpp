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
#include "../../../Util/Log.h"
#include <algorithm>
#include <dirent.h>
#include <pwd.h>
#include <sys/stat.h>
#include <unistd.h>


namespace Forge { namespace FileSystem {

namespace {
  const mode_t NewDirMode = 0644;
}

Directory::Directory():
  mCurrentPath(getenv("HOME"))
{
  passwd* userInfo = getpwuid(getuid());
  if (userInfo)
  {
    mCurrentPath = userInfo->pw_dir;
  }
}

Directory::Directory(std::string const& path):
  mCurrentPath(path)
{
  // Strip trailing '/'
  if (*path.rbegin() == '/')
  {
    mCurrentPath.pop_back();
  }
  convertToAbsolutePath();
}

std::string const& Directory::getCurrentPath() const
{
  return mCurrentPath;
}

std::string Directory::getName() const
{
  return mCurrentPath.substr(mCurrentPath.find_last_of('/')+1);
}

void Directory::goUp()
{
  mCurrentPath = getParent();
}

bool Directory::cd(std::string const& dir)
{
  Directory newDir(getCurrentPath());
  std::string::size_type startIndex = 0;
  std::string::size_type endIndex = 0;
  do
  {
    endIndex = dir.find_first_of('/', startIndex);
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

bool Directory::create()
{
  if (exists())
    return false;
  return mkdir(mCurrentPath.c_str(), NewDirMode) == 0;
}

bool Directory::exists() const
{
  struct stat buffer;
  return (stat(mCurrentPath.c_str(), &buffer) == 0 && S_ISDIR(buffer.st_mode));
}

bool Directory::contains(const std::string& name) const
{
  std::string fullPath(mCurrentPath);
  struct stat buffer;
  return stat(fullPath.append("/").append(name).c_str(), &buffer) == 0;
}

bool Directory::hasSubDir(const std::string& name) const
{
  std::string fullPath(mCurrentPath);
  struct stat buffer;
  return
      stat(fullPath.append("/").append(name).c_str(), &buffer) == 0 &&
      S_ISDIR(buffer.st_mode);
}

std::vector<std::string> Directory::listFiles() const
{
  std::vector<std::string> files;

  DIR* directory = opendir(mCurrentPath.c_str());

  if (directory == nullptr)
    return files;

  struct dirent* entry;
  std::string entryPath;
  while ((entry = readdir(directory)) != nullptr)
  {
    entryPath = mCurrentPath;
    entryPath.append("/").append(entry->d_name);
    struct stat fileInfo;
    if (lstat(entryPath.c_str(), &fileInfo) == 0 && S_ISREG(fileInfo.st_mode))
    {
      files.push_back(entryPath);
    }
  }

  closedir(directory);

  std::sort(files.begin(), files.end());

  return files;
}
std::vector<Directory> Directory::listDirectories() const
{
  std::vector<Directory> directories;

  DIR* directory = opendir(mCurrentPath.c_str());

  if (directory == nullptr)
    return directories;

  struct dirent* entry;
  std::string entryPath;
  while ((entry = readdir(directory)) != nullptr)
  {
    entryPath = mCurrentPath;
    entryPath.append("/").append(entry->d_name);
    struct stat fileInfo;
    if (lstat(entryPath.c_str(), &fileInfo) == 0 && S_ISDIR(fileInfo.st_mode))
    {
      directories.push_back(Directory(entryPath));
    }
  }

  closedir(directory);

  std::sort(
    directories.begin(),
    directories.end(),
    [](Directory const& lhs, Directory const& rhs)
    {
      return lhs.getCurrentPath() < rhs.getCurrentPath();
    }
  );

  return directories;
}

constexpr char Directory::getSeparator()
{
  return '/';
}

std::string Directory::getParent() const
{
  return mCurrentPath.substr(0, mCurrentPath.find_last_of(getSeparator()));
}

bool Directory::isAbsolutePath() const
{
  return (mCurrentPath[0] == '/');
}

void Directory::convertToAbsolutePath()
{
  if (isAbsolutePath())
    return;

  char currentDir[PATH_MAX];
  getcwd(currentDir, PATH_MAX);
  std::string currentWorkingDir(currentDir);
  std::string::size_type startIndex = 0;
  std::string::size_type endIndex = 0;
  while (endIndex != std::string::npos)
  {
    endIndex = mCurrentPath.find_first_of(getSeparator(), startIndex);
    std::string currentElement = mCurrentPath.substr(startIndex, endIndex);
    if (currentElement == "..")
    {
      // Remove one level of current working dir
      currentWorkingDir = currentWorkingDir.substr(currentWorkingDir.find_last_of('/'));
    }
    else if (currentElement != ".")
    {
      currentWorkingDir.append("/").append(currentElement);
    }
    startIndex = endIndex+1;
  }
  mCurrentPath = currentWorkingDir;
}

}}
