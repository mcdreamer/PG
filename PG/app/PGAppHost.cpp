#include <SFML/Graphics.hpp>

#include "PG/app/PGAppHost.h"

#ifdef __APPLE__

#include "PG/internal/platform/MacAppController.h"
#include "PG/internal/platform/MacResourceHandler.h"

using TAppController = PG::Internal::MacAppController;
using TResourceHandler = PG::Internal::MacResourceHandler;

#else

#include "PG/internal/platform/WinAppController.h"
#include "PG/internal/platform/WinResourceHandler.h"

using TAppController = PG::Internal::WinAppController;
using TResourceHandler = PG::Internal::WinResourceHandler;

#endif

#include "PG/internal/graphics/SFMLScene.h"
#include "PG/internal/graphics/SFMLViewHandle.h"
#include "PG/internal/input/PGKeyCodeUtils.h"

#include "PG/app/IGameController.h"

#include <memory>

namespace PG {

namespace Internal {
    
extern int g_TileSize;
extern IResourceHandler* g_ResourceHandler;
extern SFMLFontCache* g_FontCache;

}

namespace
{
    //--------------------------------------------------------
    PG::PGPoint windowPointToScenePoint(const sf::Vector2u& windowSize,
                                        const PG::PGSize& sceneSize,
                                        const PG::PGPoint& point)
    {
        return PG::PGPoint(point.x / ((double)windowSize.x / sceneSize.width),
                           point.y / ((double)windowSize.y / sceneSize.height));
        
    }

    //--------------------------------------------------------
    void handleEvents(sf::RenderWindow& window, Internal::SFMLViewHandle& viewHandle)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                viewHandle.currentScene->m_Callback->keyDown(Internal::PGKeyCodeUtils::getPGKeyCode(event.key.code), PGKeyModifierNone);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                viewHandle.currentScene->m_Callback->keyUp(Internal::PGKeyCodeUtils::getPGKeyCode(event.key.code));
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                const PG::PGPoint windowPt(event.mouseButton.x, event.mouseButton.y);
                const auto scenePt = windowPointToScenePoint(window.getSize(), viewHandle.currentScene->getSceneSize(), windowPt);
            
                viewHandle.currentScene->clickInWindow(scenePt, event.mouseButton.button == sf::Mouse::Button::Right);
            }
        }
    }
    
    //--------------------------------------------------------
    bool draw(sf::RenderWindow& window, const NodePtrArray& nodes)
    {
        bool anyNodesRemoved = false;
        
        for (const auto& child : nodes)
        {
            auto* n = dynamic_cast<Internal::ISFMLNodeProvider*>(child.get());
            if (!n->isRemoved())
            {
                window.draw(*n->getNode());
                
                auto view = window.getView();
                view.move((float)-child->getPosition().x, (float)-child->getPosition().y);
                window.setView(view);
                
                anyNodesRemoved |= draw(window, n->m_ChildNodes);
                
                view.move((float)child->getPosition().x, (float)child->getPosition().y);
                window.setView(view);
            }
            else
            {
                anyNodesRemoved = true;
            }
        }
        
        return anyNodesRemoved;
    }
    
    //--------------------------------------------------------
    void removeNodes(NodePtrArray& nodes)
    {
        auto childIt = nodes.begin();
        while (childIt != nodes.end())
        {
            auto* n = dynamic_cast<Internal::ISFMLNodeProvider*>(childIt->get());

            if (!n->isRemoved())
            {
                removeNodes(n->m_ChildNodes);
                ++childIt;
            }
            else
            {
                childIt = nodes.erase(childIt);
            }
        }
    }

	//--------------------------------------------------------
	void runMainLoop(IGameController& gameController,
					 sf::RenderWindow& window,
					 Internal::SFMLViewHandle& viewHandle,
					 TResourceHandler& resourceHandler)
	{
		sf::Font fpsFont;
		fpsFont.loadFromFile(resourceHandler.getResourcePath("OpenSans-Regular", "ttf"));

		sf::Text fps("0", fpsFont, 30);
		fps.setPosition(15, 10);
		fps.setFillColor(sf::Color(255, 255, 255));

		sf::Clock clock;

		while (window.isOpen())
		{
			float dt = clock.getElapsedTime().asSeconds();
			clock.restart();
            
			if (viewHandle.currentScene)
			{
				auto* rootNode = dynamic_cast<Internal::ISFMLNodeProvider*>(viewHandle.currentScene->m_Root.get());
				
                handleEvents(window, viewHandle);
				
                viewHandle.currentScene->update(dt);
				
                window.clear(viewHandle.currentScene->m_BackgroundColour);
				
				const bool anyNodesRemoved = draw(window, rootNode->m_ChildNodes);
				
                if (anyNodesRemoved)
                {
                    removeNodes(rootNode->m_ChildNodes);
                }
			}

			fps.setString(std::to_string((int)(1.0 / dt)));
			window.draw(fps);

			window.display();
			
			gameController.updateFinished();
		}
	}
}

//--------------------------------------------------------
void PGAppHost::runApp(IGameController& gameController)
{
    const PGSize windowSize(gameController.getWindowSize().width,
                            gameController.getWindowSize().height);

    sf::VideoMode videoMode((unsigned int)windowSize.width, (unsigned int)windowSize.height);
    
    sf::RenderWindow window(videoMode, gameController.getWindowTitle());
    window.setFramerateLimit(60);
    
    TAppController appController;
    TResourceHandler resourceHandler;
    Internal::SFMLFontCache fontCache;

    Internal::SFMLViewHandle viewHandle(&window);
    
    Internal::g_ResourceHandler = &resourceHandler;
    Internal::g_TileSize = gameController.getTileSize();
	Internal::g_FontCache = &fontCache;

    gameController.start(appController, viewHandle, resourceHandler);
    
	runMainLoop(gameController, window, viewHandle, resourceHandler);
}

}
