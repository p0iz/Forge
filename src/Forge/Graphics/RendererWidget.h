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

#pragma once

#include "OrbitalCamera.h"
#include "TestData.h"

#include <GL/glew.h>
#include <QGLWidget>

namespace Forge
{

class QtInputHandler;
class Shader;
class ShaderProgram;

class RendererWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit RendererWidget(
			Camera& camera,
			QtInputHandler& input,
			QWidget* parent=0,
			const QGLWidget* shareWidget = 0,
			Qt::WindowFlags f=0);

	void setCamera(Camera& camera)
	{
		mCamera = camera;
	}

	virtual ~RendererWidget();

	void toggleFullscreen();

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
private:

	bool mFullScreen;

	glm::mat4x4 mViewProjection;

	TestData mTestData;

	virtual void setupScene();
	virtual void drawScene();
	virtual void tearDownScene();

	Camera& mCamera;
	QtInputHandler& mInput;

	glm::mat4x4 mProjectionTx;
	glm::mat4x4 mViewTx;

	// Returns the GL format used by the widget
	static const QGLFormat widgetQGLFormat();
};

}
