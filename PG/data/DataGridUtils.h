#pragma once

#include "PG/data/DataGrid.h"

namespace PG {
namespace DataGridUtils {

//--------------------------------------------------------
template <typename T, typename TFunc>
void forEachEntry(const DataGrid<T>& dataGrid, const TFunc& func)
{
    for (int x = 0; x < dataGrid.getWidth(); ++x)
    {
        for (int y = 0; y < dataGrid.getHeight(); ++y)
        {
            func(x, y, dataGrid.at(x, y));
        }
    }
}

} // namespace DataGridUtils
}
