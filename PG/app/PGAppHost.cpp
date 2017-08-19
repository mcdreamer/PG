#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "PG/app/PGAppHost.h"
#include "PG/app/AppConfiguration.h"
#include "PG/app/AppHostServices.h"
#include "PG/console/ConsoleController.h"
#include "PG/internal/ui/Console.h"

#ifdef __APPLE__

#include "PG/internal/platform/MacPlatformServices.h"
#include "PG/internal/platform/MacResourceHandler.h"

using TPlatformServices = PG::Internal::MacPlatformServices;
using TResourceHandler = PG::Internal::MacResourceHandler;

#elif __linux__

#include "PG/internal/platform/LinuxPlatformServices.h"
#include "PG/internal/platform/LinuxResourceHandler.h"

using TPlatformServices = PG::Internal::LinuxPlatformServices;
using TResourceHandler = PG::Internal::LinuxResourceHandler;

#else

#include "PG/internal/platform/WinPlatformServices.h"
#include "PG/internal/platform/WinResourceHandler.h"

using TPlatformServices = PG::Internal::WinPlatformServices;
using TResourceHandler = PG::Internal::WinResourceHandler;

#endif

#include "PG/internal/graphics/SFMLScene.h"
#include "PG/internal/graphics/SFMLView.h"
#include "PG/internal/input/KeyCodeUtils.h"

#include "PG/app/IGameController.h"

#include "PG/sound/Sound.h"
#include "PG/sound/SoundID.h"
#include "PG/sound/ISoundController.h"
#include <map>

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
    PG::Point windowPointToScenePoint(const sf::Vector2u& windowSize,
                                        const PG::Size& sceneSize,
                                        const PG::Point& point)
    {
        return PG::Point(point.x / ((double)windowSize.x / sceneSize.width),
                           point.y / ((double)windowSize.y / sceneSize.height));

    }

	//--------------------------------------------------------
	sf::Color getsfColorFromPGColor(const PG::Colour& c)
	{
		return sf::Color(c.r, c.g, c.b, (unsigned char)c.a);
	}

	// AD: Move this to a new file?
	//--------------------------------------------------------
	class AppRunner
	{
	public:
		//--------------------------------------------------------
		AppRunner(IGameController& gameController,
				  const AppConfiguration& appConfig,
				  sf::RenderWindow& window,
				  Internal::SFMLView& view,
				  TResourceHandler& resourceHandler)
		: m_ConsoleActive(false),
		m_GameController(gameController),
		m_AppConfig(appConfig),
		m_Window(window),
		m_View(view),
		m_ResourceHandler(resourceHandler)
		{}
	
		//--------------------------------------------------------
		void runMainLoop()
		{
			sf::Font fpsFont;
			fpsFont.loadFromFile(m_ResourceHandler.getResourcePath(m_AppConfig.styleSheet.uiFontName, "ttf"));
			
			sf::Text fpsLabel("0", fpsFont, 20);
			fpsLabel.setPosition(m_Window.getSize().x - 25, m_Window.getSize().y - 25);
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
				
				drawScene(fpsLabel);
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
					
					scene->update(timestep);
					
					removeNodes(rootNode->m_ChildNodes);
				}
				
				m_GameController.updateFinished();
				
				m_View.updateFinished();
				
				unhandledTime -= timestep;
			}
		}
		
		//--------------------------------------------------------
		void drawScene(sf::Text& fpsLabel)
		{
			auto* scene = m_View.getCurrentScene();
			auto* rootNode = scene ? dynamic_cast<Internal::ISFMLNodeProvider*>(scene->getRoot().node) : nullptr;
			
			if (scene)
			{
				m_Window.clear(getsfColorFromPGColor(scene->getBackgroundColour()));
			}
			if (rootNode)
			{
				draw(rootNode->m_ChildNodes);
			}
			
			m_Window.draw(fpsLabel);
			
			m_Window.display();
		}
		
		//--------------------------------------------------------
		void handleEvents()
		{
			auto* scene = m_View.getCurrentScene();
			auto controller = scene->getController();
			
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
					const PG::Point windowPt(event.mouseButton.x, event.mouseButton.y);
					const auto scenePt = windowPointToScenePoint(m_Window.getSize(), scene->getSceneSize(), windowPt);
					
					scene->clickInScene(scenePt, event.mouseButton.button == sf::Mouse::Button::Right);
				}
			}
		}
		
		//--------------------------------------------------------
		bool draw(const NodePtrArray& nodes)
		{
			bool anyNodesRemoved = false;
			
			for (const auto& child : nodes)
			{
				auto* n = dynamic_cast<Internal::ISFMLNodeProvider*>(child.get());
				if (!n->isRemoved())
				{
					m_Window.draw(*n->getNode());
					
					auto view = m_Window.getView();
					view.move((int)-child->getPosition().x, (int)-child->getPosition().y);
					m_Window.setView(view);
					
					anyNodesRemoved |= draw(n->m_ChildNodes);
					
					view.move((int)child->getPosition().x, (int)child->getPosition().y);
					m_Window.setView(view);
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

namespace Internal {
	//--------------------------------------------------------
	class SFMLSoundController : public ISoundController
	{
	public:
		SFMLSoundController(IResourceHandler& resourceHandler)
		: m_ResourceHandler(resourceHandler), m_NextID(0)
		{}
	
		virtual SoundID registerSound(const Sound& sound) override
		{
			auto soundPath = m_ResourceHandler.getResourcePath("sound", "wav");
			
			const SoundID soundID(m_NextID++);
			
			auto& buffer = m_SoundBuffers[soundID];
			if (!buffer.loadFromFile(soundPath))
			{
				std::cerr << "Failed to load sound" << std::endl;
			}
			
			return soundID;
		}
		
		virtual void playSound(const SoundID& soundID) override
		{
			auto bufferIt = m_SoundBuffers.find(soundID);
			
			if (bufferIt != m_SoundBuffers.end())
			{
				m_Sounds.emplace_back();
				auto& sound = m_Sounds.back();
				sound.setBuffer(bufferIt->second);
				sound.play();
			}
		}
		
	private:
		std::map<SoundID, sf::SoundBuffer>	m_SoundBuffers;
		IResourceHandler&					m_ResourceHandler;
		int									m_NextID;
		std::vector<sf::Sound>				m_Sounds;
	};
}

//--------------------------------------------------------
void PGAppHost::runApp(IGameController& gameController)
{
	const auto appConfig = gameController.getConfiguration();

    sf::VideoMode videoMode((unsigned int)appConfig.windowSize.width,
							(unsigned int)appConfig.windowSize.height);

    sf::RenderWindow window(videoMode, appConfig.windowTitle);
	window.setVerticalSyncEnabled(true);

    TPlatformServices platformServices;
    TResourceHandler resourceHandler;
    Internal::SFMLFontCache fontCache;
	
	Internal::g_ResourceHandler = &resourceHandler;
	Internal::g_TileSize = appConfig.tileSize;
	Internal::g_FontCache = &fontCache;
	
	Internal::SFMLSoundController soundController(resourceHandler);
	const auto soundID = soundController.registerSound(Sound{});
	soundController.playSound(soundID);

	ConsoleController consoleController;
	consoleController.addCommandSet(getRegistryForBuiltInCommands());
	
	AppHostServices appHostServices(appConfig.styleSheet,
									consoleController,
									soundController,
									platformServices,
									resourceHandler);
	
	Internal::SFMLView view(&window, appHostServices);

    gameController.start(appHostServices, view);

	AppRunner appRunner(gameController, appConfig, window, view, resourceHandler);
	appRunner.runMainLoop();
}

}
