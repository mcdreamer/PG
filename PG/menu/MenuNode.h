#pragma once

#include <list>
#include <string>

namespace PG {

class MenuNode;
using MenuNodeList = std::list<MenuNode>;

//--------------------------------------------------------
class MenuNode
{
public:
    MenuNode()
    : m_Tag(-1)
    {}
    
    MenuNode(const std::string& text, int tag=-1)
    : m_Text(text), m_Tag(tag)
    {}
    
    const std::string&  getText() const { return m_Text; }
    int                 getTag() const { return m_Tag; }
    const MenuNodeList& getChildren() const { return m_Children; }
    bool                getHasSubMenu() const { return !m_Children.empty(); }
    
    MenuNode&           addChild(const MenuNode& child);
    
private:
    MenuNodeList        m_Children;
    
    const std::string   m_Text;
    int                 m_Tag;
};

}
