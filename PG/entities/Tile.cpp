#include "PG/entities/Tile.h"
#include "PG/data/AttributeConstants.h"

namespace PG {

//--------------------------------------------------------
bool Tile::isBlocking() const
{
    auto blocking = m_Attributes.getAttributeBool(AttributeConstants::kBlocking);
    return !blocking || blocking.get();
}

}
