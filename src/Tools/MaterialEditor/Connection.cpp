#include "Connection.hpp"
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include <QPainter>


Connection::Connection(QGraphicsItem* start):
  QObject(nullptr),
  QGraphicsLineItem(nullptr),
  mContextMenu("Connection actions"),
  mStartItem(start),
  mEndItem(nullptr)
{
  setFlag(QGraphicsItem::ItemIsSelectable);
  createMenus();
}

Connection::~Connection()
{
  if (scene())
  {
    scene()->removeItem(this);
  }
}

void Connection::setStart(QGraphicsItem* item)
{
  mStartItem = item;
}

QGraphicsItem* Connection::start()
{
  return mStartItem;
}

void Connection::setEnd(QGraphicsItem* item)
{
  mEndItem = item;
  setLine(mStartItem->x(), mStartItem->y(), mEndItem->x(), mEndItem->y());
}

QGraphicsItem* Connection::end()
{
  return mEndItem;
}

bool Connection::isNew() const
{
  return mEndItem == nullptr;
}

void Connection::updateConnectionEnd(const QPointF& newEnd)
{
  qreal dx1 = mStartItem->boundingRect().width() / 2;
  qreal dy1 = mStartItem->boundingRect().height() / 2;
  setLine(mStartItem->x() + dx1, mStartItem->y() + dy1, newEnd.x(), newEnd.y());
}

void Connection::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
  painter->save();

  painter->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);

  if (isSelected())
  {
    painter->setPen(Qt::red);
  }

  QBrush brush;
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(painter->pen().color());
  painter->setBrush(brush);

  painter->drawPath(shape());

  painter->restore();
}

QPainterPath Connection::shape() const
{
  QPointF start = line().p1();
  QPointF end = line().p2();

  QPainterPath curve(start);

  qreal xmiddle = start.x() + (end.x() - start.x()) / 2;
  qreal ymiddle = start.y() + (end.y() - start.y()) / 2;

  curve.cubicTo(xmiddle,
                start.y(),
                xmiddle,
                end.y(),
                end.x(),
                end.y());

  curve.addRect(xmiddle - 3, ymiddle - 3, 6, 6);

  QPainterPathStroker stroker;
  stroker.setWidth(3);
  return stroker.createStroke(curve);
}

void Connection::onUpdateRequested()
{
  if (mEndItem)
  {
    qreal dx1 = mStartItem->boundingRect().width() / 2;
    qreal dy1 = mStartItem->boundingRect().height() / 2;

    qreal dx2 = mEndItem->boundingRect().width() / 2;
    qreal dy2 = mEndItem->boundingRect().height() / 2;

    setLine(mStartItem->x() + dx1, mStartItem->y() + dy1, mEndItem->x() + dx2, mEndItem->y() + dy2);
  }
}

void Connection::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
  mContextMenu.exec(event->screenPos());
}

void Connection::createMenus()
{
  QAction* disconnect = mContextMenu.addAction("Disconnect");
  connect(disconnect, SIGNAL(triggered()), this, SIGNAL(removeConnection()));
}
