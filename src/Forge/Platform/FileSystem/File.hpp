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

#include <fstream>
#include <string>


namespace Forge { namespace FileSystem {

/* A class to encapsulate the file operations in one place */
class File
{
  public:
    // Use std::ios_base::in/out/app/etc when specifying access modes
    typedef std::ios_base::openmode AccessMode;

    File();
    File(
        std::string const& filename,
        AccessMode mode = std::ios_base::in | std::ios_base::out
    );

    bool exists() const;
    bool eof() const;

    void open(std::string const& filename, AccessMode mode = std::ios_base::in | std::ios_base::out);
    void close();
    void flush();

    void writeData(char const* data, int const size);
    void readData(char* container, int const maxSize);

    std::string readLine();

    template <class Writable>
    std::fstream& operator<<(Writable const& source)
    {
      if (mFileStream.is_open() && mMode & std::ios_base::out)
      {
        return mFileStream << source;
      }
    }

    template <class Readable>
    std::fstream& operator>>(Readable const& destination)
    {
      return mFileStream >> destination;
    }

    std::fstream& getFileStream();

    /* Returns the file name extension */
    static std::string getExtension(std::string const& filename);

  private:
    AccessMode mMode;
    std::fstream mFileStream;
    bool mDirty;
};

}}
