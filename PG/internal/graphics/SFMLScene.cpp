#include "PG/internal/graphics/SFMLScene.h"
#include "PG/app/AppHostServices.h"
#include "PG/animation/AnimationUpdater.h"
#include "PG/ui/UIMessageQueuePoster.h"

namespace PG {

//--------------------------------------------------------
ScenePtr SceneCreator::createScene(SceneControllerPtr& controller,
								   AppHostServices& appHostServices,
								   const Size& size)
{
	return std::make_unique<Internal::SFMLScene>(controller,
												 size,
												 appHostServices.getStyleSheet());
}

namespace Internal {

//--------------------------------------------------------
SFMLScene::SFMLScene(SceneControllerPtr& controller,
					 const Size& size,
					 const StyleSheet& styleSheet)
: m_SceneController(controller.release()),
m_SceneSize(size)
{
	m_Root = NodeCreator::createNode();
	m_UIRoot = NodeCreator::createNode();
	m_UI.reset(new PG::UI(*this));
	m_UI->setStyleSheet(styleSheet);
}

//--------------------------------------------------------
void SFMLScene::setBackgroundColour(const Colour& colour)
{
	m_BackgroundColour = colour;
}

//--------------------------------------------------------
void SFMLScene::setCamera(const Camera& camera)
{
	m_Camera = camera;
}

//--------------------------------------------------------
void SFMLScene::addAnimation(std::unique_ptr<IAnimation>& animation)
{
	m_Animations.emplace_back(animation.release());
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
UIMessageQueuePoster SFMLScene::getUIMessagePoster()
{
	return m_UI->getMessagePoster();
}

//--------------------------------------------------------
void SFMLScene::update(double dt)
{
	if (m_SceneController)
	{
		AnimationUpdater animUpdater;
		animUpdater.updateAnimations(m_Animations, dt);
		animUpdater.removeCompletedAnimations(m_Animations);
		
		m_SceneController->update(dt);
		
		if (m_Root)
		{
			m_Root->setPosition(m_Camera.calculateCameraPoint(getSceneSize(),
															  m_Root->getPosition()));
		}
	}
	
	m_UI->update();
}

}
}
