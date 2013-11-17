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


#ifndef EDITORWINDOW_HPP
#define EDITORWINDOW_HPP

#include "ui_EditorWindow.h"
#include "MaterialNode.hpp"
#include "Node.hpp"
#include "SelectNameDialog.hpp"
#include <QMainWindow>
#include <QGraphicsScene>


class EditorEventHandler;

class EditorWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit EditorWindow(QWidget *parent = 0);
    ~EditorWindow();

  private slots:
    void onNewMaterial();
    void onAddTechnique();
    void onAddTechnique(QPointF const& pos);
    void showAboutQtDialog();
    void onRemoveNode();
    void onRenameNode();

  private:
    Ui::EditorWindow* ui;
    QGraphicsScene* mScene;
    QMenu* mNodeViewContextMenu;

    void makeConnections();

    void setupNodeView();

    void createNodeViewMenu();

    template <class NodeType>
    Node* addNode(QPointF const& pos, QString const& name)
    {
      Node* node = new NodeType;

      if (SameType<NodeType, MaterialNode>::value)
      {
        ui->nodeView->setMaterialNode(node);
      }

      node->setName(name);
      node->setZValue(2);
      mScene->addItem(node);
      node->setPos(pos.x() - node->boundingRect().width() / 2, pos.y() - node->boundingRect().height() / 2);
      connect(node, SIGNAL(removeNode()), this, SLOT(onRemoveNode()));
      connect(node, SIGNAL(renameNode()), this, SLOT(onRenameNode()));
      return node;
    }

    template <class NodeType>
    Node* addNode(QString const& name)
    {
      return addNode<NodeType>(QPointF(5000, 5000), name);
    }

    template <class T, class U>
    struct SameType
    {
        static constexpr bool value = false;
    };

    template <class T>
    struct SameType<T,T>
    {
        static constexpr bool value = true;
    };

};

#endif // EDITORWINDOW_HPP
