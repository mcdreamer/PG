#pragma once

#include "PG/data/DataGrid.h"

namespace PG {

//--------------------------------------------------------
class GeometryLoader
{
public:
	DataGrid<bool> loadGeometryFile(const std::string& filename) const;
};

}
