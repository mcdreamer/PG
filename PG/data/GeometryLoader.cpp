#include "PG/data/GeometryLoader.h"

#include <fstream>

namespace PG {
	
//--------------------------------------------------------
DataGrid<bool> GeometryLoader::loadGeometryFile(const std::string& filename) const
{
	std::fstream fs;
	fs.open(filename, std::fstream::in);
	
	int width = 0;
	int height = 0;
	
	if (fs.is_open() && !fs.eof())
	{
		fs >> width;
	}
	if (fs.is_open() && !fs.eof())
	{
		fs >> height;
	}
	
	if (width > 0 && height > 0)
	{
		DataGrid<bool> geometry(width, height);
		
		const int totalPositions = width * height;
		int pos = 0;
		
		while (fs.is_open() && !fs.eof() && pos < totalPositions)
		{
			char thisPos='0';
			fs >> thisPos;
			
			if (thisPos == '-' || thisPos == '#')
			{
				geometry.set(pos % width, pos / width, thisPos == '#');
				++pos;
			}
		}
		
		if (pos == totalPositions)
		{
			return geometry;
		}
	}
	
	return DataGrid<bool>(0, 0);
}

}
