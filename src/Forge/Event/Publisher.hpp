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

#include "Util/UniqueId.hpp"

#include <unordered_set>

namespace Forge {

template <class EventType>
class Subscriber;

template <class EventType>
class Publisher
{
public:
	void publish(const EventType& event) const
	{
		for (Subscriber<EventType>* subscriber : mSubscribers)
		{
			subscriber->notify(event);
		}
	}

	bool subscribe(Subscriber<EventType>& subscriber)
	{
		if (mSubscribers.count(&subscriber) == 0)
		{
			mSubscribers.insert(&subscriber);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool unsubscribe(Subscriber<EventType>& subscriber)
	{
		return mSubscribers.erase(&subscriber);
	}

private:
	std::unordered_set<Subscriber<EventType>*> mSubscribers;
};

}
