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

namespace Forge {

MaterialParser::MaterialParser(const char* filename)
	: mXmlFile(filename), mXmlReader(&mXmlFile)
{
}

Material MaterialParser::parse()
{
	mXmlFile.open(QFile::ReadOnly | QFile::Text);
	Material parsedMaterial;
	Log().info() << "Parsing XML file...\n";
	while (!mXmlReader.atEnd())
	{
		if (mXmlReader.readNextStartElement())
		{
			QString element("Read element ");
			element.append(mXmlReader.name());
			element.append(" with attributes\n");
			for (QXmlStreamAttribute attribute : mXmlReader.attributes())
			{
				element.append(attribute.name()).append(" : ").append(attribute.value()).append("\n");
			}
			Log().info() << element.toLocal8Bit().constData() << "\n";
		}
	}
	mXmlFile.close();
	return parsedMaterial;
}

} // namespace Forge
