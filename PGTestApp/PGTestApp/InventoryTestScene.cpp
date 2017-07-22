#include "InventoryTestScene.h"
#include "TagConstants.h"

#include "PG/graphics/NodeCreator.h"
#include "PG/app/StyleSheet.h"
#include "PG/ui/PGButton.h"
#include "PG/ui/PGUIMessageQueuePoster.h"
#include "PG/ui/UIUtils.h"
#include "PG/ui/UIPositionCalculator.h"
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
	
	PG::UIPositionCalculator uiPosCalc(sceneSize);
	const auto btnPts = uiPosCalc.multipleDownCentre(sceneSize.height * 0.50, 5, sceneSize.height * 0.1);
	
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[0], "+ Heart", ButtonTags::kTagAddHeart));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[1], "- Heart", ButtonTags::kTagRemoveHeart));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[2], "+ Star", ButtonTags::kTagAddStar));
	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[3], "- Star", ButtonTags::kTagRemoveStar));

	m_Scene.scene->pushUIElement(new PG::PGButton(*this, btnPts[4], "Back", TagConstants::kPopScene));
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
	PG::UIPositionCalculator uiPosCalc(m_Scene.scene->getSceneSize());
	const auto btnPts = uiPosCalc.multipleLeftToRight(PG::PGPoint(50, 50), 5, 64);
	
	for (const auto& btnPt : btnPts)
	{
		auto itemHolderNode = PG::NodeCreator::createSpriteNode("inventorycontainer");
		auto itemHolderNodeHandle = m_Scene.scene->addChild(itemHolderNode);

		itemHolderNodeHandle.node->setPosition(btnPt);
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
	
	PG::UIPositionCalculator uiPosCalc(m_Scene.scene->getSceneSize());
	const auto btnPts = uiPosCalc.multipleLeftToRight(PG::PGPoint(50, 50), 5, 64);
	
	auto btnPtIt = btnPts.begin();

	for (const auto& inventoryItem : m_GameState->inventory.getItems())
	{
		if (btnPtIt == btnPts.end())
		{
			return;
		}
	
		const auto& btnPt = *btnPtIt;
	
		auto itemNode = PG::NodeCreator::createSpriteNode(inventoryItem.item.getImageName());
		itemNode->setPosition(btnPt);
		
		auto labelNode = PG::NodeCreator::createTextNode(m_Scene.scene->getStyleSheet().uiFontName, 10);
		labelNode->setText(inventoryItem.item.getName() + " (" + std::to_string(inventoryItem.count) + ")");
		labelNode->setColour(PG::Colour(255, 255, 255));
		labelNode->setPosition(PG::PGPoint(btnPt.x, btnPt.y + itemNode->getSize().height - 10));
		
		m_GameState->inventoryItemNodes.push_back(m_Scene.scene->addChild(itemNode));
		m_GameState->inventoryItemNodes.push_back(m_Scene.scene->addChild(labelNode));
		
		++btnPtIt;
	}
}
