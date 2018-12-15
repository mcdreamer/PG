#include <SFML/Graphics.hpp>

#include "PG/app/PGAppHost.h"
#include "PG/app/AppConfiguration.h"
#include "PG/app/AppHostServices.h"
#include "PG/console/ConsoleController.h"
#include "PG/ui/UI.h"
#include "PG/internal/ui/Console.h"
#include "PG/internal/sound/SFMLSoundController.h"
#include "PG/internal/platform/PileResourceHandler.h"

#include "stockpile/include/stockpile.h"

using TResourceHandler = PG::Internal::PileResourceHandler;

#ifdef __APPLE__

#include "PG/internal/platform/MacPlatformServices.h"

using TPlatformServices = PG::Internal::MacPlatformServices;

#elif __linux__

#include "PG/internal/platform/LinuxPlatformServices.h"
#include "PG/internal/platform/LinuxResourceHandler.h"

using TPlatformServices = PG::Internal::LinuxPlatformServices;

#else

#include "PG/internal/platform/WinPlatformServices.h"

using TPlatformServices = PG::Internal::WinPlatformServices;

#endif

#include "PG/internal/graphics/SFMLScene.h"
#include "PG/internal/graphics/SFMLView.h"
#include "PG/internal/input/KeyCodeUtils.h"

#include "PG/app/IGameController.h"

#include <boost/filesystem.hpp>

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
    PG::Point windowPointToViewPoint(const sf::Vector2u& windowSize,
									  const PG::Size& sceneSize,
									  const PG::Point& point)
    {
        return PG::Point(point.x / ((double)windowSize.x / sceneSize.width),
                           point.y / ((double)windowSize.y / sceneSize.height));

    }

	//--------------------------------------------------------
	sf::Color getsfColorFromPGColor(const PG::Colour& c)
	{
		return sf::Color(c.r, c.g, c.b, (unsigned char)(255 * c.a));
	}

	// AD: Move this to a new file?
	//--------------------------------------------------------
	class AppRunner
	{
	public:
		//--------------------------------------------------------
		AppRunner(IGameController& gameController,
				  const AppConfiguration& appConfig,
				  AppHostServices& appHostServices,
				  sf::RenderWindow& window,
				  Internal::SFMLView& view,
				  TResourceHandler& resourceHandler)
		: m_GameController(gameController),
		m_AppConfig(appConfig),
		m_AppHostServices(appHostServices),
		m_Window(window),
		m_View(view),
		m_ResourceHandler(resourceHandler),
		m_ConsoleActive(false)
		{}
	
		sf::RenderTexture	m_RenderTexture;
	
		//--------------------------------------------------------
		void runMainLoop()
		{
			m_RenderTexture.create(m_Window.getSize().x, m_Window.getSize().y);
			
			sf::Font fpsFont;
			const auto uiFontData = m_ResourceHandler.getResourceData(m_AppConfig.styleSheet.uiFontName);
			if (uiFontData.data)
			{
				fpsFont.loadFromMemory(uiFontData.data, uiFontData.size);
			}
			
			sf::Text fpsLabel("0", fpsFont, 20);
			const auto displayScale = m_AppHostServices.getPlatformServices().getDisplayScale();
			fpsLabel.setPosition((m_Window.getSize().x / displayScale) - 25,
								 (m_Window.getSize().y / displayScale) - 25);
			fpsLabel.setFillColor(sf::Color(255, 255, 255));
			
			sf::Clock clock;
			const double timestep = 1.0 / 60.0;
			double unhandledTime = 0;
			
			while (m_Window.isOpen())
			{
				const double dt = clock.getElapsedTime().asSeconds();
				unhandledTime += dt;
				clock.restart();
				fpsLabel.setString(std::to_string((int)(1.0 / dt)));
				
				performUpdates(timestep, unhandledTime);
				
				drawScene(timestep, fpsLabel);
			}
		}
		
	private:
		//--------------------------------------------------------
		void performUpdates(const double& timestep,
							double& unhandledTime)
		{
			while (unhandledTime >= timestep)
			{
				auto* scene = m_View.getCurrentScene();
				auto* rootNode = scene ? dynamic_cast<Internal::ISFMLNodeProvider*>(scene->getRoot().node) : nullptr;
				
				if (scene && rootNode)
				{
					handleEvents();
					
					m_View.update(timestep);
					
					removeNodes(rootNode->m_ChildNodes);
				}
				
				m_GameController.updateFinished();
				
				m_View.updateFinished();
				
				unhandledTime -= timestep;
			}
		}
		
		//--------------------------------------------------------
		void drawScene(const double& timestep, sf::Text& fpsLabel)
		{
			auto* scene = m_View.getCurrentScene();
			auto* rootNode = scene ? dynamic_cast<Internal::ISFMLNodeProvider*>(scene->getRoot().node) : nullptr;
			auto* uiRootNode = scene ? dynamic_cast<Internal::ISFMLNodeProvider*>(scene->getUILayer().getUIRoot().node) : nullptr;
			
			m_Window.clear();
			m_RenderTexture.clear();
			
			if (rootNode)
			{
				const auto nodeLocalOrigin = scene->getRoot().node->getRect().topLeft();
			
				auto sfmlView = m_RenderTexture.getView();
				sfmlView.move((float)-nodeLocalOrigin.x, (float)-nodeLocalOrigin.y);
				m_RenderTexture.setView(sfmlView);
				
				if (scene)
				{
					// Draw background
					sf::RectangleShape backgroundRect(sf::Vector2f(m_Window.getSize().x, m_Window.getSize().y));
					backgroundRect.setOrigin((float)nodeLocalOrigin.x, (float)nodeLocalOrigin.y);
					backgroundRect.setFillColor(getsfColorFromPGColor(scene->getBackgroundColour()));
					m_RenderTexture.draw(backgroundRect);
				}
				
				draw(rootNode->m_ChildNodes, m_RenderTexture);
				
				sfmlView.move((float)nodeLocalOrigin.x, (float)nodeLocalOrigin.y);
				m_RenderTexture.setView(sfmlView);
			}

			m_RenderTexture.display();
			
			sf::Sprite renderTextureSprite(m_RenderTexture.getTexture());
			m_Window.draw(renderTextureSprite);
			
			if (uiRootNode)
			{
				draw(uiRootNode->m_ChildNodes, m_Window);
				
				m_Window.draw(fpsLabel);
			}
			
			m_Window.display();
		}
		
		//--------------------------------------------------------
		void handleEvents()
		{
			auto* scene = m_View.getCurrentScene();
			auto controller = scene ? scene->getController() : SceneControllerHandle();
			
			if (!scene || !controller.controller)
			{
				return;
			}
			
			sf::Event event;
			while (m_Window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_Window.close();
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					const auto keyMod = Internal::KeyCodeUtils::getCurrentModifiers();
					const auto keyCode = Internal::KeyCodeUtils::getKeyCode(event.key.code);
				
					const bool showConsole = (keyMod == KeyModifier::kShift && keyCode == KeyCode::kEscape);
				
					if (!showConsole)
					{
						controller.controller->keyDown(keyCode, keyMod);
					}
					else
					{
						toggleConsole();
					}
				}
				else if (event.type == sf::Event::KeyReleased)
				{
					controller.controller->keyUp(Internal::KeyCodeUtils::getKeyCode(event.key.code));
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					const Point windowPt(event.mouseButton.x, event.mouseButton.y);
					const auto scenePt = windowPointToViewPoint(m_Window.getSize(), scene->getSceneSize(), windowPt);
					m_View.clickInView(scenePt, event.mouseButton.button == sf::Mouse::Button::Right);
				}
			}
		}
		
		
		//--------------------------------------------------------
		void draw(const NodePtrArray& nodes, sf::RenderTarget& renderTarget)
		{
			for (const auto& child : nodes)
			{
				auto* n = dynamic_cast<Internal::ISFMLNodeProvider*>(child.get()); // remove this
				if (!n->isRemoved())
				{
					renderTarget.draw(*n->getNode());
					
					const auto nodeLocalOrigin = child->getRect().topLeft();
					
					auto sfmlView = renderTarget.getView();
					sfmlView.move((int)-nodeLocalOrigin.x, (int)-nodeLocalOrigin.y);
					renderTarget.setView(sfmlView);
					
					draw(n->m_ChildNodes, renderTarget);
					
					sfmlView.move((int)nodeLocalOrigin.x, (int)nodeLocalOrigin.y);
					renderTarget.setView(sfmlView);
				}
			}
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
		void toggleConsole()
		{
			m_ConsoleActive = !m_ConsoleActive;
			
			if (m_ConsoleActive)
			{
				std::unique_ptr<ISceneController> consoleScene(new Internal::ConsoleScene);
				m_View.pushScene(consoleScene);
			}
			else
			{
				m_View.popScene();
			}
		}
		
		IGameController&		m_GameController;
		const AppConfiguration&	m_AppConfig;
		AppHostServices&		m_AppHostServices;
		sf::RenderWindow&		m_Window;
		Internal::SFMLView&		m_View;
		TResourceHandler&		m_ResourceHandler;
		bool					m_ConsoleActive;
	};
}

namespace
{
	//--------------------------------------------------------
	ConsoleCommandRegistry getRegistryForBuiltInCommands()
	{
		ConsoleCommandRegistry builtInCommands;
		builtInCommands.addHandler("version", [](const std::vector<ConsoleCommandArgument>& args) { return "PG Engine v0.1"; }, {});
		
		return builtInCommands;
	}
}

//--------------------------------------------------------
void PGAppHost::runApp(IGameController& gameController)
{
	const auto appConfig = gameController.getConfiguration();
	
	TPlatformServices platformServices;
	const auto displayScale = platformServices.getDisplayScale();

    sf::VideoMode videoMode((unsigned int)(appConfig.windowSize.width * displayScale),
							(unsigned int)(appConfig.windowSize.height * displayScale));

    sf::RenderWindow window(videoMode, appConfig.windowTitle);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
	sf::View sfmlView(sf::FloatRect(0.0f,
									0.0f,
									(float)appConfig.windowSize.width,
									(float)appConfig.windowSize.height));
	window.setView(sfmlView);

	boost::filesystem::path resourcesPath = platformServices.getResourcesFilePath();
	resourcesPath /= "resources.pile";
	auto resourceData = stockpile::loadPile(resourcesPath.string());
	if (!resourceData)
	{
		std::cerr << "Couldn't load resources" << std::endl;
		return;
	}

    TResourceHandler resourceHandler(*resourceData);
    Internal::SFMLFontCache fontCache;
	
	Internal::g_ResourceHandler = &resourceHandler;
	Internal::g_TileSize = appConfig.tileSize;
	Internal::g_FontCache = &fontCache;
	Internal::SFMLSoundController soundController(resourceHandler);

	ConsoleController consoleController;
	consoleController.addCommandSet(getRegistryForBuiltInCommands());	
	
	AppHostServices appHostServices(&gameController,
									appConfig.styleSheet,
									consoleController,
									soundController,
									platformServices,
									resourceHandler);
	
	Internal::SFMLView view(&window, appHostServices);

    gameController.start(appHostServices, view);

	AppRunner appRunner(gameController, appConfig, appHostServices, window, view, resourceHandler);
	appRunner.runMainLoop();
}

}
