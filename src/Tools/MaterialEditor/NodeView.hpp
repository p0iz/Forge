#pragma once

#include "Connection.hpp"
#include "Node.hpp"
#include <QGraphicsView>
#include <memory>


class QMenu;

class NodeView : public QGraphicsView
{
  Q_OBJECT

  signals:
    void addTechnique(QPointF const& pos);

    void nodeConnected(QGraphicsItem* item);

  public:
    explicit NodeView(QWidget* parent = nullptr);

    void setMaterialNode(Node* node);
    Node const* materialNode() const;

  protected:
    void contextMenuEvent(QContextMenuEvent* event);

    void wheelEvent(QWheelEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

  private:
    QMenu* mContextMenu;

    QAction* mAddTechniqueAction;

    Connection* mNewConnection;

    void createContextMenu();

    float mZoomMultiplier;

    Node* mMaterialNode;

  private slots:
    void onRemoveConnection();

};
