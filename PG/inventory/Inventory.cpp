#include "PG/inventory/Inventory.h"

namespace PG {

//--------------------------------------------------------
void Inventory::addItem(const InventoryItem& item)
{
	if (hasMaximumSize() && (int)m_Items.size() == *getMaximumSize())
	{
		return;
	}

	if (m_GroupMatchingItems)
	{
		auto existingIt = std::find_if(m_Items.begin(),
									   m_Items.end(),
									   [&](const auto& heldItem) { return heldItem.item.getName() == item.getName(); });
		if (existingIt != m_Items.end())
		{
			if (!m_MaxHeldItemSize.is_initialized() || existingIt->count < m_MaxHeldItemSize.get())
			{
				++existingIt->count;
			}
			
			return;
		}
	}

	m_Items.emplace_back(item, 1);
}

//--------------------------------------------------------
void Inventory::removeItem(const InventoryItem* item)
{
	auto itemIt = std::find_if(m_Items.begin(),
							   m_Items.end(),
							   [&](const auto& heldItem) { return &heldItem.item == item; });

	if (itemIt != m_Items.end())
	{
		if (itemIt->count > 1)
		{
			--itemIt->count;
		}
		else
		{
			m_Items.erase(itemIt);
		}
	}
}

}
