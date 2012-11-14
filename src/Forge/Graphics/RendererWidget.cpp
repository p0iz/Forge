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

#include "RendererWidget.h"

#include "Input/QtInputHandler.h"

#include <iostream>
#include <QMouseEvent>

namespace Forge
{

RendererWidget::RendererWidget(
		Camera& camera,
		QtInputHandler& input,
		QWidget* parent,
		const QGLWidget* shareWidget,
		Qt::WindowFlags f)
	: QGLWidget(widgetQGLFormat(), parent, shareWidget, f),
	  mCamera(camera), mInput(input)
{
	setMouseTracking(true);
}

const QGLFormat RendererWidget::widgetQGLFormat()
{
	QGLFormat format = QGLFormat::defaultFormat();
	format.setVersion(3, 3);
	format.setProfile(QGLFormat::CoreProfile);
	format.setSampleBuffers(true);
	return format;
}

RendererWidget::~RendererWidget()
{
	tearDownScene();
}

void RendererWidget::toggleFullscreen()
{
	if (mFullScreen)
	{
		showNormal();
		mFullScreen = false;
	}
	else
	{
		showFullScreen();
		mFullScreen = true;
	}
}

void RendererWidget::setupScene()
{
	mTestData.create();
}

void RendererWidget::drawScene()
{
	mTestData.draw(mCamera.getViewProjectionMatrix(), mCamera.getViewMatrix());
}

void RendererWidget::tearDownScene()
{
	mTestData.destroy();
}

void RendererWidget::initializeGL()
{
	// Flag to load all extensions, needed by OpenGL 3.3
	glewExperimental = GL_TRUE;
	assert(glewInit() == GLEW_OK);

	glGetError();

	glClearColor(0.6f,0.6f,0.7f,1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	setupScene();
}

void RendererWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	mCamera.setPerspectiveProjection(45.0f, w, h, 0.1f, 100.0f);
	mTestData.updateText(w, h);
}

void RendererWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	mCamera.updateViewProjectionMatrix();

	drawScene();

	swapBuffers();
}

void RendererWidget::keyPressEvent(QKeyEvent *event)
{
	mInput.keyPress(event, this);
}

void RendererWidget::keyReleaseEvent(QKeyEvent* event)
{
	mInput.keyRelease(event, this);
}

void RendererWidget::mousePressEvent(QMouseEvent *event)
{
	mInput.mousePress(event, this);
}

void RendererWidget::mouseMoveEvent(QMouseEvent *event)
{
	mInput.mouseMove(event, this);
}

}
