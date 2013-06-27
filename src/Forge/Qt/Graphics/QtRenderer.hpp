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

#include "Event/Publisher.hpp"

#include "Graphics/Renderer.h"
#include "Graphics/ResizeEvent.h"
#include "Graphics/Scene/SceneConfig.hpp"

#include <QGLWidget>

namespace Forge
{

class QtInputHandler;
class Shader;
class ShaderProgram;

class QtRenderer : public QGLWidget, public Publisher<ResizeEvent>
{
	Q_OBJECT
public:
	QtRenderer(QWidget* parent = 0, const QGLWidget* shareWidget = 0, Qt::WindowFlags f=0);
	virtual ~QtRenderer();

	void render(const SceneConfig& scene);
	void toggleFullscreen();
signals:
	void glInitialized();
protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
private:
	bool mFullScreen;

	Renderer mRenderer;

	// Returns the GL format used by the widget
	static const QGLFormat widgetQGLFormat();
};

}
