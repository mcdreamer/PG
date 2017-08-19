#pragma once

namespace PG {

struct StyleSheet;
class ConsoleController;
class ISoundController;
class IPlatformServices;
class IResourceHandler;

//--------------------------------------------------------
class AppHostServices
{
public:
	AppHostServices(const StyleSheet& styleSheet,
					ConsoleController& consoleController,
					ISoundController& soundController,
					IPlatformServices& platformServices,
					IResourceHandler& resourceHandler)
	: m_StyleSheet(styleSheet),
	m_ConsoleController(consoleController),
	m_SoundController(soundController),
	m_PlatformServices(platformServices),
	m_ResourceHandler(resourceHandler)
	{}
	
	const StyleSheet&	getStyleSheet() const { return m_StyleSheet; }
	ConsoleController&	getConsoleController() { return m_ConsoleController; }
	ISoundController&	getSoundController() { return m_SoundController; }
	IPlatformServices&	getPlatformServices() { return m_PlatformServices; }
	IResourceHandler&	getResourceHandler() { return m_ResourceHandler; }
	
private:
	const StyleSheet&	m_StyleSheet;
	ConsoleController&	m_ConsoleController;
	ISoundController&	m_SoundController;
	IPlatformServices&	m_PlatformServices;
	IResourceHandler&	m_ResourceHandler;
};

}
