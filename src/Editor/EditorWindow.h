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

#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>

#include <memory>

namespace Ui {
class EditorWindow;
}

// Forward declarations
namespace Forge {
class Engine;
class QtEngineState;
class QtGameStateMachine;
class OrbitalCamera;
class RendererWidget;
} // Forge

class EditorInputHandler;
class MaterialEditorView;

class EditorWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit EditorWindow(QWidget *parent = 0);
	~EditorWindow();

private slots:
	void on_actionTools_activated();

	void on_actionToggle_Debug_Axis_triggered();

	void on_debugAxisCheckBox_clicked(bool checked);
private:
	Ui::EditorWindow *ui;

	std::shared_ptr<Forge::QtGameStateMachine> mEditorStateMachine;
	std::shared_ptr<Forge::Engine> mEngine;
	std::shared_ptr<Forge::OrbitalCamera> mCamera;
	std::shared_ptr<EditorInputHandler> mInput;
	std::shared_ptr<Forge::RendererWidget> mRenderer;
	std::shared_ptr<MaterialEditorView> mMaterialEditor;
	std::shared_ptr<Forge::QtEngineState> mEditorState;
};

#endif // EDITORWINDOW_H
