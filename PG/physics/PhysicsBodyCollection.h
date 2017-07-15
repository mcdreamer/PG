#pragma once

#include "PG/graphics/Node.h"
#include "PG/physics/PhysicsBody.h"
#include "PG/physics/PhysicsWorld.h"

namespace PG {

//--------------------------------------------------------
class PhysicsBodyCollection
{
private:
	//--------------------------------------------------------
	class CollisionTracker : public PG::PhysicsWorldCallback
	{
	public:
		CollisionTracker(std::vector<size_t>& collectedItems_)
		: collectedItems(collectedItems_)
		{}
		
		std::vector<size_t>& collectedItems;
		
		//--------------------------------------------------------
		virtual void bodiesDidCollide(const PG::PhysicsBody& body,
									  const PG::PhysicsBody& collidedWithBody,
									  const size_t nthBody) override
		{
			collectedItems.push_back(nthBody);
		}
	};
	
public:
	//--------------------------------------------------------
	void addItemWithBody(const int& item, PG::NodeHandle nodeHandle, const PG::PhysicsBody& body)
	{
		m_Items.push_back(item);
		m_ItemNodes.push_back(nodeHandle);
		m_ItemBodies.push_back(body);
	}
	
	//--------------------------------------------------------
	template <typename TCollidedWithBodyFunc>
	void findCollisionsWithBodyInWorld(const PG::PhysicsBody& body,
									   const PG::PhysicsWorld& world,
									   const TCollidedWithBodyFunc& collidedWithBodyFunc)
	{
		CollisionTracker collisionTracker(m_CollectedItems);
		world.findCollisionsWithBody(body, m_ItemBodies, collisionTracker);
		
		std::sort(m_CollectedItems.begin(), m_CollectedItems.end());
		std::reverse(m_CollectedItems.begin(), m_CollectedItems.end());
		while (!m_CollectedItems.empty())
		{
			auto itemIt = m_Items.begin();
			auto itemNodeIt = m_ItemNodes.begin();
			auto itemBodyIt = m_ItemBodies.begin();
			
			const auto itemIndex = m_CollectedItems.front();
			std::advance(itemIt, itemIndex);
			std::advance(itemNodeIt, itemIndex);
			std::advance(itemBodyIt, itemIndex);
			
			itemNodeIt->node->removeFromParent();
			
			collidedWithBodyFunc(*itemIt);
			
			m_Items.erase(itemIt);
			m_ItemNodes.erase(itemNodeIt);
			m_ItemBodies.erase(itemBodyIt);
			
			m_CollectedItems.erase(m_CollectedItems.begin());
		}
	}
	
private:
	std::vector<int>				m_Items;
	std::vector<PG::NodeHandle>		m_ItemNodes;
	std::vector<PG::PhysicsBody>	m_ItemBodies;
	std::vector<size_t>				m_CollectedItems;
};

}
