#pragma once

#include "PG/data/Attributes.h"

#include <string>
#include <vector>

namespace PG {

//--------------------------------------------------------
class InventoryItem
{
public:
    InventoryItem(const std::string& name, const std::string& imageName, const Attributes& attributes)
    : m_Name(name), m_ImageName(imageName), m_Attributes(attributes)
    {}
    
    const std::string& 	getName() const { return m_Name; }
    const std::string& 	getImageName() const { return m_ImageName; }
    const Attributes&   getAttributes() const { return m_Attributes; }
    
    Attributes&         getAttributes() { return m_Attributes; }

private:
    std::string         m_Name;
    std::string         m_ImageName;
    Attributes          m_Attributes;
};

class InventoryItemArray : public std::vector<InventoryItem> {};

}
