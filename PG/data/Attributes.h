#pragma once

#include <boost/optional.hpp>

#include <string>
#include <map>

namespace PG {

//--------------------------------------------------------
class Attributes
{
    using Map = std::map<std::string, std::string>;
    
public:
    boost::optional<std::string>    getAttributeString(const std::string& name) const;
    boost::optional<int>            getAttributeInt(const std::string& name) const;
    boost::optional<bool>           getAttributeBool(const std::string& name) const;
    bool                            hasAttribute(const std::string& name) const;

    void        setAttributeString(const std::string& name, const std::string& value);
    void        setAttributeInt(const std::string& name, const int& value);
    void        setAttributeBool(const std::string& name, const bool& value);
    void        removeAttribute(const std::string& name);
    
    typename Map::iterator          begin() { return m_Attributes.begin(); }
    typename Map::iterator          end() { return m_Attributes.end(); }
    
    typename Map::const_iterator    begin() const { return m_Attributes.begin(); }
    typename Map::const_iterator    end() const { return m_Attributes.end(); }
    
private:
    Map         m_Attributes;
};

}
