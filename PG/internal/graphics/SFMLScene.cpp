#include "PG/internal/graphics/SFMLScene.h"

namespace PG {

//--------------------------------------------------------
ScenePtr SceneCreator::createScene(SceneControllerPtr& controller, const PGSize& size, const StyleSheet& styleSheet)
{
    return std::make_unique<Internal::SFMLScene>(controller, size, styleSheet);
}

namespace Internal {

//--------------------------------------------------------
SFMLScene::SFMLScene(SceneControllerPtr& controller, const PGSize& size, const StyleSheet& styleSheet)
: m_SceneController(controller.release()), m_SceneSize(size)
{
	m_Root = NodeCreator::createNode();
	m_UI.reset(new PG::PGUI(*this));
	m_UI->setStyleSheet(styleSheet);
}

//--------------------------------------------------------
void SFMLScene::setBackgroundColour(const Colour& colour)
{
	m_BackgroundColour = colour;
}

//--------------------------------------------------------
NodeHandle SFMLScene::addChild(std::unique_ptr<INode>& node)
{
	return m_Root->addChild(node);
}

//--------------------------------------------------------
PGSize SFMLScene::getSceneSize() const
{
	return PGSize(m_SceneSize.width, m_SceneSize.height);
}

//--------------------------------------------------------
PGPoint SFMLScene::getWindowPointAsScenePoint(const PGPoint& windowPt, INode* layer) const
{
	return windowPt;
}

//--------------------------------------------------------
const StyleSheet& SFMLScene::getStyleSheet() const
{
	return m_UI->getStyleSheet();
}

//--------------------------------------------------------
void SFMLScene::clickInScene(PG::PGPoint pt, bool isRightClick)
{
	if (!m_UI->handleClick(pt) && m_SceneController)
	{
		m_SceneController->clickInScene(pt, isRightClick);
	}
}
//--------------------------------------------------------
void SFMLScene::pushUIElement(PGUIElement* uiElement)
{
	m_UI->pushElement(uiElement);
}

//--------------------------------------------------------
void SFMLScene::update(float dt)
{
	if (m_SceneController)
	{
		m_SceneController->update(dt);
	}
	
	m_UI->update();
}

}
}
