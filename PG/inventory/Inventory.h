#pragma once

#include "PG/inventory/InventoryItem.h"

#include <boost/optional.hpp>

namespace PG {

//--------------------------------------------------------
class Inventory
{
public:
	Inventory(const bool groupMatchingItems,
			  const boost::optional<int> maxSize,
			  const boost::optional<int> maxHeldItemSize)
	: m_GroupMatchingItems(groupMatchingItems),
	m_MaxSize(maxSize),
	m_MaxHeldItemSize(maxHeldItemSize)
	{}

	//--------------------------------------------------------
	struct HeldItem
	{
		HeldItem(const InventoryItem& item_, const int count_)
		: item(item_), count(count_)
		{}
		
		InventoryItem	item;
		int				count;
	};
	
	using HeldItemArray = std::vector<HeldItem>;

	void                        addItem(const InventoryItem& item);
    const HeldItemArray&		getItems() const { return m_Items; }
	
	void                        removeItem(const InventoryItem* item);
	
	bool						hasMaximumSize() const { return m_MaxSize.is_initialized(); }
	const int*					getMaximumSize() const { return hasMaximumSize() ? &m_MaxSize.get() : nullptr; }
	
private:
    HeldItemArray				m_Items;
	bool						m_GroupMatchingItems;
	boost::optional<int>		m_MaxSize;
	boost::optional<int>		m_MaxHeldItemSize;
};

}
