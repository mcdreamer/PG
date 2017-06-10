#pragma once

#include "PG/data/Attributes.h"

#include <string>
#include <vector>

namespace PG {

//--------------------------------------------------------
class Tile
{
public:
    Tile()
    {}
    
    Tile(const std::string& name, const std::string& imageName, const Attributes& attributes)
    : m_Name(name), m_ImageName(imageName), m_Attributes(attributes)
    {}
    
    const std::string&  getName() const { return m_Name; }
    const std::string&  getImageName() const { return m_ImageName; }
    bool                isBlocking() const;
    
private:
    std::string         m_Name;
    std::string         m_ImageName;
    Attributes          m_Attributes;
};

class TileArray : public std::vector<Tile> {};

}
