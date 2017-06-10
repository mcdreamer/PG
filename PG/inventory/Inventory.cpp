#include "PG/inventory/Inventory.h"

namespace PG {

//--------------------------------------------------------
void Inventory::addItem(const InventoryItem& item)
{
    m_Items.push_back(item);
}

}
