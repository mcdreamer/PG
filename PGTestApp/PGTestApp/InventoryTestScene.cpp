#include "InventoryTestScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/app/StyleSheet.h"
#include "PG/ui/PGButton.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/ui/UIUtils.h"
#include "PG/data/DataGrid.h"
#include "PG/entities/TilePositionCalculator.h"
#include "PG/core/BindableValue.h"

#include "PG/inventory/Inventory.h"
#include "PG/inventory/InventoryItem.h"

namespace
{
	//--------------------------------------------------------
	enum ButtonTags {
		kTagAddHeart = 0,
		kTagRemoveHeart,
		kTagAddStar,
		kTagRemoveStar
	};
}

//--------------------------------------------------------
struct InventoryTestScene::GameState
{
	GameState()
	: inventory(true, 5, 5)
	{}

	std::vector<PG::NodeHandle> inventoryItemNodes;
	PG::Inventory				inventory;
};

//--------------------------------------------------------
InventoryTestScene::InventoryTestScene(PG::PGTagReciever& appTagTarget)
: m_AppTagTarget(appTagTarget), 
m_GameState(new GameState)
{}

//--------------------------------------------------------
InventoryTestScene::~InventoryTestScene()
{
}

//--------------------------------------------------------
void InventoryTestScene::initScene(PG::SceneHandle scene)
{
	m_Scene = scene;
	
	m_Scene.scene->setBackgroundColour(PG::Colour(239, 247, 197));
	
	const auto sceneSize = m_Scene.scene->getSceneSize();
	
	drawInventoryBackground();
	
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width * 0.4, sceneSize.height * 0.75), "+ Heart", ButtonTags::kTagAddHeart));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width * 0.6, sceneSize.height * 0.75), "- Heart", ButtonTags::kTagRemoveHeart));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width * 0.4, sceneSize.height * 0.85), "+ Star", ButtonTags::kTagAddStar));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width * 0.6, sceneSize.height * 0.85), "- Star", ButtonTags::kTagRemoveStar));

	m_Scene.scene->pushUIElement(new PG::PGButton(*this, PG::PGPoint(sceneSize.width / 2.0, sceneSize.height * 0.95), "Back", TagConstants::kPopScene));
}

namespace
{
	//--------------------------------------------------------
	void findAndRemoveInventoryItem(PG::Inventory& inventory, const std::string& itemName)
	{
		const auto& items = inventory.getItems();
		for (const auto& item : items)
		{
			if (item.item.getName() == itemName)
			{
				inventory.removeItem(&item.item);
				
				return;
			}
		}
	}
}

//--------------------------------------------------------
void InventoryTestScene::receiveTag(const int tag, PG::PGUIMessageQueuePoster& msgPoster)
{
	switch (tag)
	{
		case kTagAddHeart:
			m_GameState->inventory.addItem(PG::InventoryItem("Heart", "heart", PG::Attributes()));
			updateInventory();
			break;
			
		case kTagRemoveHeart:
			findAndRemoveInventoryItem(m_GameState->inventory, "Heart");
			updateInventory();
			break;

		case kTagAddStar:
			m_GameState->inventory.addItem(PG::InventoryItem("Star", "star", PG::Attributes()));
			updateInventory();
			break;

		case kTagRemoveStar:
			findAndRemoveInventoryItem(m_GameState->inventory, "Star");
			updateInventory();
			break;

		default:
			msgPoster.postMessage(PG::PGUIMessage::sendTag(&m_AppTagTarget, tag));
	}
}

//--------------------------------------------------------
void InventoryTestScene::update(float dt)
{
}

//--------------------------------------------------------
void InventoryTestScene::keyDown(PG::PGKeyCode code, PG::PGKeyModifier mods)
{
}

//--------------------------------------------------------
void InventoryTestScene::keyUp(PG::PGKeyCode code)
{
}

//--------------------------------------------------------
void InventoryTestScene::drawInventoryBackground()
{
	const double y = 50;
	double x = 50;
	
	for (int i = 0; i < 5; ++i)
	{
		auto itemHolderNode = PG::NodeCreator::createSpriteNode("inventorycontainer");
		auto itemHolderNodeHandle = m_Scene.scene->addChild(itemHolderNode);

		itemHolderNodeHandle.node->setPosition(PG::PGPoint(x, y));
		
		x += itemHolderNodeHandle.node->getSize().width;
	}
}

//--------------------------------------------------------
void InventoryTestScene::updateInventory()
{
	for (auto& inventoryItemNode : m_GameState->inventoryItemNodes)
	{
		if (inventoryItemNode.node)
		{
			inventoryItemNode.node->removeFromParent();
		}
	}
	
	m_GameState->inventoryItemNodes.clear();
	
	const double y = 50;
	double x = 50;
	
	for (const auto& inventoryItem : m_GameState->inventory.getItems())
	{
		auto itemNode = PG::NodeCreator::createSpriteNode(inventoryItem.item.getImageName());
		itemNode->setPosition(PG::PGPoint(x, y));
		
		auto labelNode = PG::NodeCreator::createTextNode(m_Scene.scene->getStyleSheet().uiFontName, 10);
		labelNode->setText(inventoryItem.item.getName() + " (" + std::to_string(inventoryItem.count) + ")");
		labelNode->setColour(PG::Colour(255, 255, 255));
		labelNode->setPosition(PG::PGPoint(x, y + itemNode->getSize().height - 10));
		
		m_GameState->inventoryItemNodes.push_back(m_Scene.scene->addChild(itemNode));
		m_GameState->inventoryItemNodes.push_back(m_Scene.scene->addChild(labelNode));
		
		x += 64;
	}
}
