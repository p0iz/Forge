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

#include "Node.hpp"
#include <QMenu>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>


Node::Node(QColor const& start, QColor const& end, QGraphicsItem* parent):
  QObject(),
  QGraphicsItem(parent),
  mBackground(),
  mContextMenu("Node actions"),
  mName("Node")
{
  mBackground.setColorAt(0, start);
  mBackground.setColorAt(1, end);
  mBackground.setStart(0, 0);
  mBackground.setFinalStop(0, boundingRect().height());
  setFlag(ItemIsMovable);
  setFlag(ItemIsSelectable);
  createMenus();
}

Node::~Node()
{
}

QRectF Node::boundingRect() const
{
  return QRectF(0, 0, 200, 50);
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)

  // Set node colors in subclasses
  painter->save();
  painter->setBrush(mBackground);
  painter->setPen(Qt::black);
  painter->drawRoundedRect(boundingRect(), 15, 15);
  QTextOption textOption;
  textOption.setAlignment(Qt::AlignCenter);
  painter->drawText(boundingRect(), mName, textOption);
  painter->restore();

  emit updateConnections();
}

void Node::setName(const QString& name)
{
  mName = name;
}

const QString& Node::name() const
{
  return mName;
}

void Node::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
  mContextMenu.exec(event->screenPos());
}

void Node::createMenus()
{
  QAction* removeAction = mContextMenu.addAction("Remove node");
  connect(removeAction, SIGNAL(triggered()), this, SIGNAL(removeNode()));
  QAction* renameAction = mContextMenu.addAction("Rename node...");
  connect(renameAction, SIGNAL(triggered()), this, SIGNAL(renameNode()));
}

