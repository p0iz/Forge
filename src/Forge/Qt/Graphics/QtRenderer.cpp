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

#include "Graphics/QtRenderer.hpp"
#include "Graphics/Scene/SceneConfig.hpp"

#include "Input/QtInputHandler.h"

#include "Util/Log.h"

#include <iostream>
#include <QMouseEvent>

namespace Forge
{

QtRenderer::QtRenderer(
		QtInputHandler& input,
		Camera& camera,
		QWidget* parent,
		const QGLWidget* shareWidget,
		Qt::WindowFlags f)
		: QGLWidget(widgetQGLFormat(), parent, shareWidget, f),
		mFullScreen(false), mInput(input), mCamera(camera) {
	setMouseTracking(true);
}

const QGLFormat QtRenderer::widgetQGLFormat()
{
	QGLFormat format = QGLFormat::defaultFormat();
	format.setVersion(3, 3);
	format.setProfile(QGLFormat::CoreProfile);
	format.setSampleBuffers(true);
	return format;
}

QtRenderer::~QtRenderer() { }

void QtRenderer::toggleFullscreen()
{
	if (mFullScreen) {
		showNormal();
	} else {
		showFullScreen();
	}
	mFullScreen = !mFullScreen;
}

void QtRenderer::initializeGL()
{
	mRenderer.initialize();
	// Inform OpenGL users that the functions are available
	glewInitialized();
}

void QtRenderer::resizeGL(int w, int h)
{
	mCamera.setPerspectiveProjection(w, h);
	mRenderer.updateViewport(w, h);
}

void QtRenderer::paintGL()
{
	swapBuffers();
}

void QtRenderer::keyPressEvent(QKeyEvent *event)
{
	mInput.keyPress(event, this);
}

void QtRenderer::keyReleaseEvent(QKeyEvent* event)
{
	mInput.keyRelease(event, this);
}

void QtRenderer::mousePressEvent(QMouseEvent *event)
{
	mInput.mousePress(event, this);
}

void QtRenderer::mouseMoveEvent(QMouseEvent *event)
{
	mInput.mouseMove(event, this);
}

void QtRenderer::render(const Forge::SceneConfig& sceneConfig)
{
	updateGL();
	mRenderer.render(sceneConfig);
}

}