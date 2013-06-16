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

#include "OpenGLPropertiesDialog.h"
#include "ui_OpenGLPropertiesDialog.h"

class QGLContext;

OpenGLPropertyTableModel OpenGLPropertiesDialog::OpenGLProperties;

OpenGLPropertiesDialog::OpenGLPropertiesDialog(QGLContext* context, QWidget* parent)
	: QDialog(parent),
	  ui(new Ui::OpenGLPropertiesDialog)
{
	ui->setupUi(this);
	OpenGLProperties.populateProperties(context);
	tableProxy.setSourceModel(&OpenGLPropertiesDialog::OpenGLProperties);
	ui->glPropertyTable->setModel(&tableProxy);
}

OpenGLPropertiesDialog::~OpenGLPropertiesDialog()
{
	delete ui;
}
