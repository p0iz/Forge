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

#include "Attachable.hpp"

namespace Forge {

Attachable::Attachable(std::size_t maxAttachments) : mMaxAttachments(maxAttachments) { }

void Attachable::attachToNode(std::size_t node)
{
	if (mAttachedNodes.size() < mMaxAttachments || mMaxAttachments == 0) {
		mAttachedNodes.insert(node);
	}
}

void Attachable::detachFromNode(std::size_t node)
{
	mAttachedNodes.erase(node);
}

const std::unordered_set<std::size_t>& Attachable::getAttachedNodes() const
{
	return mAttachedNodes;
}

}
