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

#include "MaterialNode.hpp"
#include "PropertiesDialog.hpp"
#include <QPainter>


MaterialNode::MaterialNode(QGraphicsItem* parent):
  Node(QColor(64, 16, 16), QColor(255, 128, 128), parent)
{
}

MaterialNode::~MaterialNode()
{
}

void MaterialNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
  PropertiesDialog dialog;
  dialog.setName(mName);
  dialog.setDescription(mDescription);
  if (dialog.exec() == QDialog::Accepted)
  {
    qDebug("Update model");
    mName = dialog.name();
    mDescription = dialog.description();
    update();
  }
  else
  {
    qDebug("Discard changes");
  }
}


