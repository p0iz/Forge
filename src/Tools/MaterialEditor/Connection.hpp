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
#include <QGraphicsLineItem>
#include <QMenu>


// Connections are not parented, so memory management is your responsibility
class Connection : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
  public:
    explicit Connection(QGraphicsItem* start);
    virtual ~Connection();


    void setStart(QGraphicsItem* item);
    QGraphicsItem* start();

    void setEnd(QGraphicsItem* item);
    QGraphicsItem* end();

    bool isNew() const;

    void updateConnectionEnd(QPointF const& newEnd);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual QPainterPath shape() const;

  public slots:
    void onUpdateRequested();

  signals:
    void removeConnection();

  protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

  private:
    QMenu mContextMenu;

    void createMenus();

    QGraphicsItem* mStartItem;

    QGraphicsItem* mEndItem;

    QPointF mNewConnectionEnd;

};
