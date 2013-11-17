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

#include "EditorWindow.hpp"
#include "ui_EditorWindow.h"

#include "MaterialNode.hpp"
#include "NodeView.hpp"
#include "TechniqueNode.hpp"
#include <QGraphicsRectItem>
#include <QLineEdit>
#include "../../Forge/Util/Log.h"


EditorWindow::EditorWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::EditorWindow),
  mScene(new QGraphicsScene(this)),
  mNodeViewContextMenu(new QMenu(this))
{
  ui->setupUi(this);
  makeConnections();

  setupNodeView();
}

EditorWindow::~EditorWindow()
{
  delete ui;
}

void EditorWindow::onNewMaterial()
{
  SelectNameDialog selectName;
  if (selectName.exec() == QDialog::Accepted)
  {
    mScene->clear();
    ui->nodeView->resetMatrix();
    addNode<MaterialNode>(selectName.name());
    ui->nodeView->centerOn(5000, 5000);
  }
}

void EditorWindow::onAddTechnique()
{
  onAddTechnique(QPointF(5000, 5000));
}

void EditorWindow::onAddTechnique(QPointF const& pos)
{
  Forge::Log::info << "Adding technique at (" << pos.x() << "," << pos.y() << ")\n";
  SelectNameDialog selectName;
  if (selectName.exec() == QDialog::Accepted)
  {
    addNode<TechniqueNode>(pos, selectName.name());
  }
}

void EditorWindow::showAboutQtDialog()
{
  QApplication::aboutQt();
}

void EditorWindow::onRemoveNode()
{
  Node* senderNode = static_cast<Node*>(sender());

  mScene->removeItem(senderNode);

  if (senderNode == ui->nodeView->materialNode())
  {
    ui->nodeView->setMaterialNode(nullptr);
    mScene->clear();
  }
}

void EditorWindow::onRenameNode()
{
  Node* node = static_cast<Node*>(sender());
  SelectNameDialog selectName(node->name());
  if (selectName.exec() == QDialog::Accepted)
  {
    node->setName(selectName.name());
    node->update();
  }
}

void EditorWindow::makeConnections()
{
  connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui->actionNewMaterial, SIGNAL(triggered()), this, SLOT(onNewMaterial()));
  connect(ui->actionAddTechnique, SIGNAL(triggered()), this, SLOT(onAddTechnique()));
  connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(showAboutQtDialog()));
  connect(
    ui->actionResetView,
    &QAction::triggered,
    [this](){
      ui->nodeView->fitInView(mScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
  );
  connect(ui->nodeView, SIGNAL(addTechnique(QPointF const&)), this, SLOT(onAddTechnique(QPointF const&)));
}

void EditorWindow::setupNodeView()
{
  ui->nodeView->setSceneRect(QRectF(0, 0, 10000, 10000));
  ui->nodeView->centerOn(5000, 5000);
  ui->nodeView->setScene(mScene);

  createNodeViewMenu();
}

void EditorWindow::createNodeViewMenu()
{
  QAction* newMatAction = mNodeViewContextMenu->addAction("New material...");
  connect(newMatAction, SIGNAL(triggered()), this, SLOT(onNewMaterial()));
  QAction* addTechAction = mNodeViewContextMenu->addAction("Add technique...");
  connect(addTechAction, SIGNAL(triggered()), this, SLOT(onAddTechnique()));
}
