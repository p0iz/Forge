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

#include "File.hpp"


namespace Forge { namespace FileSystem {

File::File():
  mMode(),
  mFileStream(),
  mDirty(false)
{
}

File::File(const std::string& filename, AccessMode mode):
  mMode(mode),
  mFileStream(filename, mMode),
  mDirty(false)
{
}

bool File::exists() const
{
  return mFileStream.is_open();
}

void File::open(const std::string& filename, File::AccessMode mode)
{
  if (mFileStream.is_open())
  {
    mFileStream.close();
  }

  mFileStream.open(filename, mode);
  mDirty = false;
}

void File::close()
{
  mFileStream.close();
  mDirty = false;
}

void File::flush()
{
  mFileStream.flush();
}

void File::writeData(char const* data, int const size)
{
  if (mMode & std::ios_base::out)
  {
    mFileStream.write(data, size);
  }
}

void File::readData(char* container, int const maxSize)
{
  if (mMode & std::ios_base::in)
  {
    mFileStream.read(container, maxSize);
  }
}

bool File::eof() const
{
  return !mFileStream.is_open() || mFileStream.eof();
}

std::string File::readLine()
{
  std::string line;
  if (!eof())
  {
    std::getline(mFileStream, line);
  }
  return line;
}

std::string File::getExtension(std::string const& filename)
{
  std::string::size_type lastDotIdx = filename.find_last_of('.');
  return (lastDotIdx == std::string::npos) ? "" : filename.substr(lastDotIdx+1);
}

}}
