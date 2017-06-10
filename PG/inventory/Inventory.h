#pragma once

#include "PG/inventory/InventoryItem.h"

namespace PG {

//--------------------------------------------------------
class Inventory
{
public:
    const InventoryItemArray&   getItems() const { return m_Items; }
    void                        addItem(const InventoryItem& item);
    
private:
    InventoryItemArray          m_Items;
};

}
