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

#include <QObject>
#include <QGraphicsItem>
#include <QMenu>
#include <QBrush>
#include <QPen>


// This is a single node class
class Node : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
  public:
    explicit Node(QColor const& start, QColor const& end, QGraphicsItem* parent = nullptr);
    virtual ~Node();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    void setName(QString const& name);
    QString const& name() const;

  signals:
    void removeNode();

    void renameNode();

    void updateConnections();

  protected:
    QString mName;

    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

  private:
    QLinearGradient mBackground;
    QMenu mContextMenu;

    void createMenus();

};
