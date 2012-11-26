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

#include "MaterialParser.h"

#include "Util/Log.h"

#include <string>

#include <QXmlStreamReader>
#include <QFile>

namespace Forge {

Material MaterialParser::parse(std::string filename)
{
	QFile xmlFile(filename.c_str());
	xmlFile.open(QFile::ReadOnly | QFile::Text);
	QXmlStreamReader xmlReader(&xmlFile);

	Material parsedMaterial;
	Log().info() << "Parsing XML file...\n";
	while (!xmlReader.atEnd())
	{
		if (xmlReader.readNextStartElement())
		{
			QString element("Read element ");
			element.append(xmlReader.name());
			element.append(" with attributes\n");
			for (QXmlStreamAttribute attribute : xmlReader.attributes())
			{
				element.append(attribute.name()).append(" : ").append(attribute.value()).append("\n");
			}
			Log().info() << element.toLocal8Bit().constData() << "\n";
		}
	}
	xmlFile.close();
	return parsedMaterial;
}

} // namespace Forge
