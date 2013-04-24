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

/* This class provides unique identifiers for a class of objects */

namespace Forge {

typedef unsigned long long f_uid_t;

template <class T>
class UniqueId {
public:
	UniqueId() : mId(UniqueId::nextId++) { }
	f_uid_t getID() const;
private:
	f_uid_t mId;
	static f_uid_t nextId;
};

template <class T>
f_uid_t UniqueId<T>::nextId = 0;

template <class T>
f_uid_t UniqueId<T>::getID() const
{
	return mId;
}

}
