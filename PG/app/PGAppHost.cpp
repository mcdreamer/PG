#include <SFML/Graphics.hpp>

#include "PG/app/PGAppHost.h"
#include "PG/app/AppConfiguration.h"
#include "PG/app/AppHostServices.h"
#include "PG/console/ConsoleController.h"
#include "PG/internal/ui/Console.h"
#include "PG/internal/sound/SFMLSoundController.h"

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

#include <memory>
#include <cmath>

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
		return sf::Color(c.r, c.g, c.b, (unsigned char)255 * c.a);
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
	
		sf::RenderTexture	m_RenderTexture;
		sf::Shader			m_LightingShader;
	
		//--------------------------------------------------------
		void runMainLoop()
		{
			m_RenderTexture.create(m_Window.getSize().x, m_Window.getSize().y);
			const auto lightingShaderPath = m_ResourceHandler.getResourcePath("lighting", "shader");
			if (!m_LightingShader.loadFromFile(lightingShaderPath, sf::Shader::Fragment))
			{
				std::cerr << "Error loading lighting shader" << std::endl;
			}
			
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
					
					scene->update(timestep);
					
					removeNodes(rootNode->m_ChildNodes);
				}
				
				m_GameController.updateFinished();
				
				m_View.updateFinished();
				
				unhandledTime -= timestep;
			}
		}
		
		float x = 0;
		
		//--------------------------------------------------------
		void drawScene(const double& timestep, sf::Text& fpsLabel)
		{
			auto* scene = m_View.getCurrentScene();
			auto* rootNode = scene ? dynamic_cast<Internal::ISFMLNodeProvider*>(scene->getRoot().node) : nullptr;
			auto* uiRootNode = scene ? dynamic_cast<Internal::ISFMLNodeProvider*>(scene->getUIRoot().node) : nullptr;
			
			m_Window.clear();
			m_RenderTexture.clear();
				
//			if (scene)
//			{
//				sf::RectangleShape backgroundRect(sf::Vector2f(800, 600));
//				backgroundRect.setOrigin(400, 300);
//				backgroundRect.setFillColor(getsfColorFromPGColor(scene->getBackgroundColour()));
//				m_RenderTexture.draw(backgroundRect);
//			}
			
			if (rootNode)
			{
				const auto nodePos = scene->getRoot().node->getPosition();
			
				auto sfmlView = m_RenderTexture.getView();
				sfmlView.move((float)-nodePos.x, (float)-nodePos.y);
				m_RenderTexture.setView(sfmlView);
				
				if (scene)
				{
					sf::RectangleShape backgroundRect(sf::Vector2f(800, 600));
					backgroundRect.setOrigin(nodePos.x, nodePos.y);
					backgroundRect.setFillColor(getsfColorFromPGColor(scene->getBackgroundColour()));
					m_RenderTexture.draw(backgroundRect);
				}
				
				draw(rootNode->m_ChildNodes, m_RenderTexture);
				
				sfmlView.move((float)nodePos.x, (float)nodePos.y);
				m_RenderTexture.setView(sfmlView);
			}

			m_RenderTexture.display();
			
			sf::Sprite s(m_RenderTexture.getTexture());
			m_LightingShader.setUniform("texture", sf::Shader::CurrentTexture);
			m_LightingShader.setUniform("ambientLight", 0.5f);
			
			sf::Glsl::Vec2 lightPts[3];
			float lightRadii[3];
			lightPts[0] = sf::Glsl::Vec2(450.0f, 350.0f);
			lightPts[1] = sf::Glsl::Vec2(60.0f, 350.0f);
			lightPts[2] = sf::Glsl::Vec2(60.0f, 140.0f);
			lightRadii[0] = 260.0f;// + (std::sin(x) * 100.0f);
			lightRadii[1] = 260.0f;
			lightRadii[2] = 300.0f;
			x += timestep;
			
			m_LightingShader.setUniformArray("lightPts", lightPts, 3);
			m_LightingShader.setUniformArray("lightRadii", lightRadii, 3);
			
			if (scene && scene->getRoot().node)
			{
				m_LightingShader.setUniform("sceneOffset", sf::Glsl::Vec2(((float)scene->getRoot().node->getPosition().x),
																		  ((float)scene->getRoot().node->getPosition().y)));
				
				m_LightingShader.setUniform("sceneSize", sf::Glsl::Vec2(scene->getSceneSize().width, scene->getSceneSize().height));
			}
			
			m_Window.draw(s, &m_LightingShader);
			
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
		void draw(const NodePtrArray& nodes, sf::RenderTarget& renderTarget)
		{
			for (const auto& child : nodes)
			{
				auto* n = dynamic_cast<Internal::ISFMLNodeProvider*>(child.get()); // remove this
				if (!n->isRemoved())
				{
					renderTarget.draw(*n->getNode());
					
					auto sfmlView = renderTarget.getView();
					sfmlView.move((int)-child->getPosition().x, (int)-child->getPosition().y);
					renderTarget.setView(sfmlView);
					
					draw(n->m_ChildNodes, renderTarget);
					
					sfmlView.move((int)child->getPosition().x, (int)child->getPosition().y);
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
	const auto displayScale = 1.0f;//platformServices.getDisplayScale();

    sf::VideoMode videoMode((unsigned int)(appConfig.windowSize.width * displayScale),
							(unsigned int)(appConfig.windowSize.height * displayScale));

    sf::RenderWindow window(videoMode, appConfig.windowTitle);
	window.setVerticalSyncEnabled(true);
	
	sf::View sfmlView(sf::FloatRect(0.0f,
									0.0f,
									(float)appConfig.windowSize.width,
									(float)appConfig.windowSize.height));
	window.setView(sfmlView);

    TResourceHandler resourceHandler;
    Internal::SFMLFontCache fontCache;
	
	Internal::g_ResourceHandler = &resourceHandler;
	Internal::g_TileSize = appConfig.tileSize;
	Internal::g_FontCache = &fontCache;
	Internal::SFMLSoundController soundController(resourceHandler);

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
