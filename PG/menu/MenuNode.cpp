#include "PG/menu/MenuNode.h"

namespace PG {

//--------------------------------------------------------
MenuNode& MenuNode::addChild(const MenuNode& child)
{
    m_Children.insert(m_Children.end(), child);

    return *this;
}

}
