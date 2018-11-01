#include "MacResourceHandler.h"
#include "stockpile/include/stockpile.h"

namespace PG {
namespace Internal {

//--------------------------------------------------------
ResourceData MacResourceHandler::getResourceData(const std::string& resourcePath)
{
    const auto* chunk = m_Pile.getChunk(stockpile::ResourcePath("test"));
    if (chunk)
    {
        auto data = chunk->getResource(stockpile::ResourcePath(resourcePath));
        if (!data.empty())
        {
            return { data.getData(), (size_t)data.getSize() };
        }
    }

    return {};
}

}
}
