#pragma once

#include "PG/io/IResourceHandler.h"

#include <string>

namespace stockpile {
    class Pile;
}

namespace PG {
namespace Internal {

//--------------------------------------------------------
class MacResourceHandler : public IResourceHandler
{
public:
    MacResourceHandler(const stockpile::Pile& pile)
    : m_Pile(pile)
    {}

    virtual ResourceData getResourceData(const std::string& resourcePath) override;

private:
    const stockpile::Pile& m_Pile;
};

}
}
