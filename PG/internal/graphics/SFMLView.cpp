#include "PG/internal/graphics/SFMLView.h"
#include "PG/app/AppHostServices.h"
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
	return createAndInitialiseScene(sceneController);
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
		if (m_PendingSceneOperationType.get() == PendingSceneOperationType::kReplace)
		{
			m_SceneStack = std::stack<ScenePtr>();
		}
		
		createAndInitialiseScene(m_PendingSceneController);
	}
	
	m_PendingSceneController.release();
	m_PendingSceneOperationType.reset();
}

//--------------------------------------------------------
SceneControllerHandle SFMLView::createAndInitialiseScene(SceneControllerPtr& sceneController)
{
	const auto size = m_View->getView().getSize();
	
	m_SceneStack.push(SceneCreator::createScene(sceneController,
												m_AppHostServices,
												Size(size.x, size.y)));
	
	auto* scene = getCurrentScene();
	SceneControllerHandle controllerHandle(scene ? scene->getController() : nullptr);
	
	if (controllerHandle.controller)
	{
		controllerHandle.controller->initScene(m_AppHostServices, scene);
	}
	
	return controllerHandle;
}

}
}
