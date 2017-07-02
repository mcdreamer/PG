#include "PG/internal/graphics/SFMLView.h"
#include "PG/core/Size.h"

#include <SFML/Graphics.hpp>

namespace PG {
namespace Internal {

//--------------------------------------------------------
SceneControllerHandle SFMLView::replaceScene(SceneControllerPtr& sceneController)
{
	m_PendingSceneController.reset(sceneController.release());
	m_PendingSceneOperationType = PendingSceneOperationType::kReplace;
	
	return SceneControllerHandle(m_PendingSceneController.get());
}

//--------------------------------------------------------
SceneControllerHandle SFMLView::pushScene(SceneControllerPtr& sceneController)
{
	m_PendingSceneController.reset(sceneController.release());
	m_PendingSceneOperationType = PendingSceneOperationType::kPush;
	
	return SceneControllerHandle(m_PendingSceneController.get());
}

//--------------------------------------------------------
void SFMLView::popScene()
{
	m_PendingSceneOperationType = PendingSceneOperationType::kPop;
}

//--------------------------------------------------------
SceneControllerHandle SFMLView::addOverlay(SceneControllerPtr& sceneController)
{
	const auto size = m_View->getView().getSize();

	m_SceneStack.push(SceneCreator::createScene(m_PendingSceneController, PGSize(size.x, size.y), m_StyleSheet));
	
	auto* scene = getCurrentScene();
	SceneControllerHandle controllerHandle(scene ? scene->getController() : nullptr);
	
	if (controllerHandle.controller)
	{
		controllerHandle.controller->initScene(scene);
	}
	
	return controllerHandle;
}

//--------------------------------------------------------
void SFMLView::removeOverlay(const SceneControllerHandle& sceneController)
{
}

//--------------------------------------------------------
void SFMLView::updateFinished()
{
	presentPendingSceneIfAny();
}

//--------------------------------------------------------
IScene*	SFMLView::getCurrentScene() const
{
	return !m_SceneStack.empty() ? m_SceneStack.top().get() : nullptr;
}

//--------------------------------------------------------
void SFMLView::presentPendingSceneIfAny()
{
	if (!m_PendingSceneOperationType.is_initialized())
	{
		return;
	}

	if (m_PendingSceneOperationType.get() == PendingSceneOperationType::kPop)
	{
		if (!m_SceneStack.empty())
		{
			m_SceneStack.pop();
		}
	}
	else if (m_PendingSceneController)
	{
		const auto size = m_View->getView().getSize();
		
		if (m_PendingSceneOperationType.get() == PendingSceneOperationType::kReplace)
		{
			m_SceneStack = std::stack<ScenePtr>();
		}
		
		m_SceneStack.push(SceneCreator::createScene(m_PendingSceneController, PGSize(size.x, size.y), m_StyleSheet));
		
		auto* scene = getCurrentScene();
		SceneControllerHandle controllerHandle(scene ? scene->getController() : nullptr);
		
		if (controllerHandle.controller)
		{
			controllerHandle.controller->initScene(scene);
		}
	}
	
	m_PendingSceneController.release();
	m_PendingSceneOperationType.reset();
}

}
}
