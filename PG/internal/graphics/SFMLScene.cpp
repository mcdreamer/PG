#include "PG/internal/graphics/SFMLScene.h"

namespace PG {

//--------------------------------------------------------
ScenePtr SceneCreator::createScene(SceneControllerPtr& controller, const Size& size, const StyleSheet& styleSheet)
{
    return std::make_unique<Internal::SFMLScene>(controller, size, styleSheet);
}

namespace Internal {

//--------------------------------------------------------
SFMLScene::SFMLScene(SceneControllerPtr& controller, const Size& size, const StyleSheet& styleSheet)
: m_SceneController(controller.release()), m_SceneSize(size)
{
	m_Root = NodeCreator::createNode();
	m_UI.reset(new PG::UI(*this));
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
Size SFMLScene::getSceneSize() const
{
	return Size(m_SceneSize.width, m_SceneSize.height);
}

//--------------------------------------------------------
Point SFMLScene::getWindowPointAsScenePoint(const Point& windowPt, INode* layer) const
{
	return windowPt;
}

//--------------------------------------------------------
const StyleSheet& SFMLScene::getStyleSheet() const
{
	return m_UI->getStyleSheet();
}

//--------------------------------------------------------
void SFMLScene::clickInScene(PG::Point pt, bool isRightClick)
{
	if (!m_UI->handleClick(pt) && m_SceneController)
	{
		m_SceneController->clickInScene(pt, isRightClick);
	}
}
//--------------------------------------------------------
void SFMLScene::pushUIElement(UIElement* uiElement)
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
