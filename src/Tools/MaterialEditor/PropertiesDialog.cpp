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


#include "PropertiesDialog.hpp"
#include "ui_PropertiesDialog.h"

PropertiesDialog::PropertiesDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PropertiesDialog)
{
  ui->setupUi(this);
}

PropertiesDialog::~PropertiesDialog()
{
  delete ui;
}

void PropertiesDialog::setName(const QString& name)
{
  ui->nameEdit->setText(name);
}

QString PropertiesDialog::name() const
{
  return ui->nameEdit->text();
}

void PropertiesDialog::setDescription(const QString& desc)
{
  ui->descriptionEdit->setText(desc);
}

QString PropertiesDialog::description() const
{
  return ui->descriptionEdit->text();
}
