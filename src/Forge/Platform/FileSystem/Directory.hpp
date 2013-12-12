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

#include "ForgeExport.h"
#include <string>
#include <vector>


namespace Forge { namespace FileSystem {

class FORGE_EXPORT Directory
{
  public:
    Directory();
    explicit Directory(std::string const& path);

    static char const SEPARATOR;

    std::string const& getCurrentPath() const;
    std::string getName() const;
    void goUp();
    bool cd(std::string const& dir);

    // Operate on this directory
    bool exists() const;
    bool create();

    static std::string getCurrentWorkingDir();

    // Operate on children
    bool contains(std::string const& name) const;
    bool hasSubDir(std::string const& name) const;
    bool createDir(std::string const& name);
    bool createFile(std::string const& name);

    std::vector<std::string> listFiles() const;
    std::vector<Directory> listDirectories() const;

    std::string getParent() const;

    bool isAbsolutePath() const;

  private:
    std::string mCurrentPath;
    void convertToAbsolutePath();
};

}}
