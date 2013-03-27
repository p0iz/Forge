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
 * Copyright 2012 Tommi Martela
 *
 */

#include "EditorWindow.h"
#include "ui_EditorWindow.h"

#include "EditorInputHandler.h"

// Editor includes
#include "EditorViews/MaterialEditorView.hpp"

// Forge includes
#include "Engine.h"
#include "Graphics/OrbitalCamera.h"
#include "Graphics/QtRenderer.hpp"
#include "State/QtGameState.h"
#include "State/QtStateMachine.hpp"
#include "State/GameStateLibrary.hpp"

#include <QTabWidget>

void EditorWindow::initializeForge()
{
	mGameClock.init();
	Forge::GameStateLibrary::getSingleton().add(mEditorState->getName(), mEditorState);
	mEditorStateMachine.init(mEditorState);
	mEditorStateMachine.start();
}
EditorWindow::EditorWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::EditorWindow),
	mEngine(new Forge::Engine(*mEditorStateMachine)),
	mCamera(new Forge::OrbitalCamera(10.0f)),
	mInput(new EditorInputHandler(*mCamera)),
	mRenderer(new Forge::QtRenderer(*mCamera, *mInput, 0, 0, 0)),
	mMaterialEditor(new MaterialEditorView(*mCamera, *mInput)),
	mEditorState(
		new Forge::QtGameState(QString("EditorState"), *mRenderer, *mInput, mGameClock))
{
	QTabWidget* tabWidget = new QTabWidget();
	tabWidget->addTab(mRenderer.get(), tr("World renderer"));
	tabWidget->addTab(mMaterialEditor.get(), tr("Material editor"));

	initializeForge();

	ui->setupUi(this);
	ui->centralwidget->setParent(0);
	QMainWindow::setCentralWidget(tabWidget);

	QObject::connect(
				tabWidget, SIGNAL(currentChanged(int)), ui->toolStack, SLOT(setCurrentIndex(int)));

	QObject::connect(
				ui->reloadShaders_world, SIGNAL(clicked()), mRenderer.get(), SLOT(reloadMaterials()));

	ui->toolStack->setCurrentIndex(0);
	tabWidget->setCurrentIndex(0);
}

EditorWindow::~EditorWindow()
{
	mEngine->stop();
	delete ui;
}

void EditorWindow::on_actionToggle_Debug_Axis_triggered()
{
	Forge::DebugAxis::toggleDebuggingInfo();
}

void EditorWindow::on_debugAxisCheckBox_clicked(bool checked)
{
	Forge::DebugAxis::setDebuggingInfo(checked);
}
