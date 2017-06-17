#include <SFML/Graphics.hpp>

#include "PG/app/PGAppHost.h"
#include "PG/app/AppConfiguration.h"

#ifdef __APPLE__

#include "PG/internal/platform/MacPlatformServices.h"
#include "PG/internal/platform/MacResourceHandler.h"

using TPlatformServices = PG::Internal::MacPlatformServices;
using TResourceHandler = PG::Internal::MacResourceHandler;

#else

#include "PG/internal/platform/WinPlatformServices.h"
#include "PG/internal/platform/WinResourceHandler.h"

using TPlatformServices = PG::Internal::WinPlatformServices;
using TResourceHandler = PG::Internal::WinResourceHandler;

#endif

#include "PG/internal/graphics/SFMLScene.h"
#include "PG/internal/graphics/SFMLView.h"
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
	sf::Color getsfColorFromPGColor(const PG::Colour& c)
	{
		return sf::Color(c.r, c.g, c.b, (unsigned char)c.a);
	}

    //--------------------------------------------------------
    void handleEvents(sf::RenderWindow& window, Internal::SFMLView& view)
    {
		auto* scene = view.getCurrentScene();
		auto controller = scene->getController();
		
		if (!scene || !controller.controller)
		{
			return;
		}
	
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                controller.controller->keyDown(Internal::PGKeyCodeUtils::getPGKeyCode(event.key.code), PGKeyModifierNone);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                controller.controller->keyUp(Internal::PGKeyCodeUtils::getPGKeyCode(event.key.code));
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                const PG::PGPoint windowPt(event.mouseButton.x, event.mouseButton.y);
                const auto scenePt = windowPointToScenePoint(window.getSize(), scene->getSceneSize(), windowPt);
            
                scene->clickInScene(scenePt, event.mouseButton.button == sf::Mouse::Button::Right);
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
                view.move((int)-child->getPosition().x, (int)-child->getPosition().y);
                window.setView(view);
                
                anyNodesRemoved |= draw(window, n->m_ChildNodes);
                
                view.move((int)child->getPosition().x, (int)child->getPosition().y);
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
					 const AppConfiguration& appConfig,
					 sf::RenderWindow& window,
					 Internal::SFMLView& view,
					 TResourceHandler& resourceHandler)
	{
		sf::Font fpsFont;
		fpsFont.loadFromFile(resourceHandler.getResourcePath(appConfig.styleSheet.uiFontName, "ttf"));

		sf::Text fps("0", fpsFont, 20);
		fps.setPosition(window.getSize().x - 25, window.getSize().y - 25);
		fps.setFillColor(sf::Color(255, 255, 255));

		sf::Clock clock;

		while (window.isOpen())
		{
			float dt = clock.getElapsedTime().asSeconds();
			clock.restart();
			
			auto* scene = view.getCurrentScene();
			if (scene)
			{
				auto* rootNode = dynamic_cast<Internal::ISFMLNodeProvider*>(scene->getRoot().node);
				
                handleEvents(window, view);
				
                scene->update(dt);
				
                window.clear(getsfColorFromPGColor(scene->getBackgroundColour()));
				
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
			
			view.updateFinished();
		}
	}
}

//--------------------------------------------------------
void PGAppHost::runApp(IGameController& gameController)
{
	const auto appConfig = gameController.getConfiguration();

    sf::VideoMode videoMode((unsigned int)appConfig.windowSize.width,
							(unsigned int)appConfig.windowSize.height);
    
    sf::RenderWindow window(videoMode, appConfig.windowTitle);
    window.setFramerateLimit(60);
    
    TPlatformServices platformServices;
    TResourceHandler resourceHandler;
    Internal::SFMLFontCache fontCache;

    Internal::SFMLView view(&window, appConfig.styleSheet);
    
    Internal::g_ResourceHandler = &resourceHandler;
    Internal::g_TileSize = appConfig.tileSize;
	Internal::g_FontCache = &fontCache;

    gameController.start(platformServices, view, resourceHandler);
    
	runMainLoop(gameController, appConfig, window, view, resourceHandler);
}

}
