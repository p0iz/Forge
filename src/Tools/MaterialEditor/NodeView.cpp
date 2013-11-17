#include "NodeView.hpp"
#include "Node.hpp"
#include <QContextMenuEvent>
#include <QMenu>
#include <QWheelEvent>


NodeView::NodeView(QWidget* parent):
  QGraphicsView(parent),
  mContextMenu(new QMenu(this)),
  mZoomMultiplier(1.15f),
  mAddTechniqueAction(nullptr),
  mNewConnection(nullptr),
  mMaterialNode(nullptr)
{
  createContextMenu();
}

void NodeView::setMaterialNode(Node* node)
{
  mMaterialNode = node;
}

Node const* NodeView::materialNode() const
{
  return mMaterialNode;
}

void NodeView::contextMenuEvent(QContextMenuEvent* event)
{
  if (!itemAt(event->pos()))
  {
    mAddTechniqueAction->setEnabled(mMaterialNode != nullptr);
    QAction* selected = mContextMenu->exec(event->globalPos());

    if (selected == mAddTechniqueAction)
    {
      emit addTechnique(mapToScene(event->pos()));
    }
  }
  else
  {
    QGraphicsView::contextMenuEvent(event);
  }
}

void NodeView::wheelEvent(QWheelEvent* event)
{
  if (event->delta() > 0)
  {
    scale(mZoomMultiplier, mZoomMultiplier);
  }
  else
  {
    scale(1.0f / mZoomMultiplier, 1.0f / mZoomMultiplier);
  }
}

void NodeView::mousePressEvent(QMouseEvent* event)
{
  Node* item = static_cast<Node*>(itemAt(event->pos()));
  if (item && event->modifiers() & Qt::ShiftModifier)
  {
    // Start drawing a new connection arrow
    mNewConnection = new Connection(item);
    scene()->addItem(mNewConnection);
    QPointF sceneEventPos(mapToScene(event->pos()));
    qDebug("Starting new connection at (%.2f,%.2f).", sceneEventPos.x(), sceneEventPos.y());
    mNewConnection->updateConnectionEnd(sceneEventPos);
    connect(item, SIGNAL(updateConnections()), mNewConnection, SLOT(onUpdateRequested()));
    connect(item, SIGNAL(removeNode()), mNewConnection, SIGNAL(removeConnection()));
    connect(mNewConnection, SIGNAL(removeConnection()), this, SLOT(onRemoveConnection()));
  }
  else
  {
    QGraphicsView::mousePressEvent(event);
  }
}

void NodeView::mouseMoveEvent(QMouseEvent* event)
{
  // if we are dragging a connection,
  // update the end point to the current mouse position
  if (mNewConnection)
  {
    QPointF newEnd(mapToScene(event->pos()));
    mNewConnection->updateConnectionEnd(newEnd);
  }
  QGraphicsView::mouseMoveEvent(event);
}

void NodeView::mouseReleaseEvent(QMouseEvent* event)
{
  if (mNewConnection)
  {
    QGraphicsItem* item = static_cast<Node*>(itemAt(event->pos()));
    if (!item || item == mNewConnection || item == mNewConnection->start())
    {
      qDebug("Cancelling new connection");
      delete mNewConnection;
    }
    else
    {
      Node* node = static_cast<Node*>(item);
      qDebug("Accepting connection");
      mNewConnection->setEnd(item);

      connect(node, SIGNAL(updateConnections()), mNewConnection, SLOT(onUpdateRequested()));
      connect(node, SIGNAL(removeNode()), mNewConnection, SIGNAL(removeConnection()));
    }
    mNewConnection = nullptr;
  }
  QGraphicsView::mouseReleaseEvent(event);
}

void NodeView::createContextMenu()
{
  mAddTechniqueAction = mContextMenu->addAction("Add technique...");
}

void NodeView::onRemoveConnection()
{
  sender()->deleteLater();
}
