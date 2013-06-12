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
#include "Graphics/DebugAxis.h"
#include "Graphics/OrbitalCamera.h"
#include "Graphics/QtRenderer.hpp"
#include "State/QtGameState.h"
#include "State/QtStateMachine.hpp"
#include "State/GameStateLibrary.hpp"

#include <QTabWidget>

EditorWindow::EditorWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::EditorWindow),
	mCamera(new Forge::OrbitalCamera(10.0f)),
	mInput(new EditorInputHandler(*mCamera)),
	mRenderer(new Forge::QtRenderer),
	mMaterialEditor(new MaterialEditorView),
	mEditorState(new Forge::QtGameState(QString("EditorState"),
										  *mCamera,
										  *mRenderer,
										  *mInput,
										  mGameClock,
										  mSceneConfig))
{
	initializeForge();
	initializeUi();
	QObject::connect(mRenderer.get(), &Forge::QtRenderer::glewInitialized,
					 mEditorState.get(), &Forge::QtGameState::createState);
}

void EditorWindow::initializeForge()
{
	mGameClock.init();
	Forge::GameStateLibrary::getSingleton().add(mEditorState->getName(), mEditorState);
	mEditorStateMachine.init(mEditorState);
	mEditorStateMachine.start();
}

void EditorWindow::initializeUi()
{
	mRenderer->installEventFilter(mInput.get());
	ui->setupUi(this);
	ui->centralwidget->setParent(0);
	ui->toolStack->setCurrentIndex(0);
	QMainWindow::setCentralWidget(mRenderer.get());
}

EditorWindow::~EditorWindow()
{
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
