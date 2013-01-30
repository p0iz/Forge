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

#include <iosfwd>

namespace Forge { namespace HashUtils {

/* Template for FNV hash function
 * FNV: http://www.isthe.com/chongo/tech/comp/fnv/
 */

/* Automatically determine architecture-specific initial values */

template <int>
struct FnvArchParameters
{
	static const size_t prime;
	static const size_t init;
};

/* 64-bit */

template <>
struct FnvArchParameters<8>
{
	static const size_t prime = 1099511628211u;
	static const size_t init = 14695981039346656037u;
};

/* 32-bit */

template <>
struct FnvArchParameters<4>
{
	static const size_t prime = 16777619u;
	static const size_t init = 2166136261u;
};

typedef FnvArchParameters<sizeof(size_t)> FnvParameters;

template <unsigned int N, unsigned int Iterator>
struct FnvHash
{
	static size_t Hash(const char (&str)[N])
	{
		return (FnvHash<N, Iterator-1>::Hash(str) ^ str[Iterator-1]) * FnvParameters::prime;
	}
};

template <unsigned int N>
struct FnvHash<N, 1>
{
	static size_t Hash(const char (&str)[N])
	{
		return (FnvParameters::init ^ str[0]) * FnvParameters::prime;
	}
};

// This class uses template expansion when possible to determine the hash value
class StringHash
{
public:
	template <unsigned int N>
	inline StringHash(const char (&str)[N+1])
		: mValue(FnvHash<N, N>::Hash(str))
	{
	}

	explicit StringHash(const std::string& targetString);

	operator size_t()
	{
		return mValue;
	}

private:
	size_t mValue;
};

size_t calculateFnv(const std::string& str);

}}
