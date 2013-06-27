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

QtRenderer::QtRenderer(QWidget* parent, const QGLWidget* shareWidget, Qt::WindowFlags f)
	: QGLWidget(widgetQGLFormat(), parent, shareWidget, f), mFullScreen(false)
{
	setMouseTracking(true);
}

const QGLFormat QtRenderer::widgetQGLFormat() {
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
	glInitialized();
}

void QtRenderer::resizeGL(int w, int h)
{
	mRenderer.updateViewport(w, h);
	publish(ResizeEvent(w, h));
}

void QtRenderer::render(const Forge::SceneConfig& sceneConfig)
{
	mRenderer.render(sceneConfig);
	swapBuffers();
}

}
