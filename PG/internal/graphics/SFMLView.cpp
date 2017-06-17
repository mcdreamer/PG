#include "PG/internal/graphics/SFMLView.h"
#include "PG/core/Size.h"

#include <SFML/Graphics.hpp>

namespace PG {
namespace Internal {

//--------------------------------------------------------
SceneControllerHandle SFMLView::presentScene(SceneControllerPtr& sceneController)
{
	m_PendingSceneController.reset(sceneController.release());
	return SceneControllerHandle(m_PendingSceneController.get());
}

//--------------------------------------------------------
void SFMLView::updateFinished()
{
	presentPendingSceneIfAny();
}

//--------------------------------------------------------
void SFMLView::presentPendingSceneIfAny()
{
	if (!m_PendingSceneController)
	{
		return;
	}

	const auto size = m_View->getView().getSize();
	
	m_CurrentScene = SceneCreator::createScene(m_PendingSceneController, PGSize(size.x, size.y), m_StyleSheet);
	m_PendingSceneController.release();
	
	SceneControllerHandle controllerHandle(m_CurrentScene->getController());
	
	if (controllerHandle.controller)
	{
		controllerHandle.controller->initScene(m_CurrentScene.get());
	}
}

}
}
