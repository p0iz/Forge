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

#include <unordered_set>

namespace Forge {

class Attachable {
public:
	/* Allow limiting the max number of attached nodes */
  explicit Attachable(std::size_t maxAttachments = 0);
  void attachToNode(std::size_t node);
  void detachFromNode(std::size_t node);
  const std::unordered_set<std::size_t>& getAttachedNodes() const;
private:
  const std::size_t mMaxAttachments;
  std::unordered_set<std::size_t> mAttachedNodes;
};

}
