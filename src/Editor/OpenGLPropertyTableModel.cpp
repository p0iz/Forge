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

#include "OpenGLPropertyTableModel.h"

#include "Graphics/QtRenderer.hpp"
#include "Util/Log.h"

#include <QGLContext>

#include <GL/glew.h>

#define MAKE_PAIR(EXP) { EXP, #EXP }

OpenGLPropertyTableModel::OpenGLPropertyTableModel(QObject* parent)
	: QAbstractTableModel(parent)
{
}

int OpenGLPropertyTableModel::rowCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return properties.size();
}

int OpenGLPropertyTableModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 2;
}

QVariant OpenGLPropertyTableModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || index.row() >= properties.size() || index.row() < 0)
		return QVariant();

	if (role == Qt::DisplayRole)
	{
		switch (index.column())
		{
		case 0:
			return properties.at(index.row()).first;
		case 1:
			return properties.at(index.row()).second;
		default:
			break;
		}
	}
	return QVariant();
}

QVariant OpenGLPropertyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case 0:
			return tr("Property");
		case 1:
			return tr("Value");
		default:
			break;
		}
	}
	return QVariant();
}

void OpenGLPropertyTableModel::populateProperties(QGLContext* context)
{
	// Populate properties table
	static const QPair<GLenum, QString> glProperties[] = {
		MAKE_PAIR(GL_MAJOR_VERSION),
		MAKE_PAIR(GL_MINOR_VERSION),
		MAKE_PAIR(GL_MAX_VARYING_COMPONENTS),
		MAKE_PAIR(GL_MAX_ATTRIB_STACK_DEPTH),
		MAKE_PAIR(GL_MAX_COMBINED_ATOMIC_COUNTERS),
		MAKE_PAIR(GL_MAX_COMPUTE_UNIFORM_COMPONENTS),
		MAKE_PAIR(GL_MAX_COLOR_ATTACHMENTS)
	};
}
