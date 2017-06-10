#include "PG/data/Attributes.h"

#include <boost/algorithm/string/predicate.hpp>

namespace PG {

//--------------------------------------------------------
boost::optional<std::string> Attributes::getAttributeString(const std::string& name) const
{
    auto valIt = m_Attributes.find(name);
    if (valIt != m_Attributes.end())
    {
        return valIt->second;
    }
    
    return boost::none;
}

//--------------------------------------------------------
boost::optional<int> Attributes::getAttributeInt(const std::string& name) const
{
    auto value = getAttributeString(name);
    if (value && !value->empty())
    {
        return std::atoi(value->c_str());
    }
    
    return boost::none;
}

//--------------------------------------------------------
boost::optional<bool> Attributes::getAttributeBool(const std::string& name) const
{
    auto value = getAttributeString(name);
    if (value && !value->empty())
    {
        return boost::iequals(*value, "yes") || boost::iequals(*value, "true");
    }
    
    return boost::none;
}

//--------------------------------------------------------
bool Attributes::hasAttribute(const std::string& name) const
{
    return m_Attributes.find(name) != m_Attributes.end();
}

//--------------------------------------------------------
void Attributes::setAttributeString(const std::string& name, const std::string& value)
{
    m_Attributes[name] = value;
}

//--------------------------------------------------------
void Attributes::setAttributeInt(const std::string& name, const int& value)
{
    setAttributeString(name, std::to_string(value));
}

//--------------------------------------------------------
void Attributes::setAttributeBool(const std::string& name, const bool& value)
{
    setAttributeString(name, value ? "true" : "false");
}

//--------------------------------------------------------
void Attributes::removeAttribute(const std::string& name)
{
    auto it = m_Attributes.find(name);
    if (it != m_Attributes.end())
    {
        m_Attributes.erase(it);
    }
}

}
