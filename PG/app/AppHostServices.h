#pragma once

namespace PG {

class TagReceiver;
struct StyleSheet;
class ConsoleController;
class ISoundController;
class IPlatformServices;
class IResourceHandler;

//--------------------------------------------------------
class AppHostServices
{
public:
	AppHostServices(TagReceiver* uiParent,
					const StyleSheet& styleSheet,
					ConsoleController& consoleController,
					ISoundController& soundController,
					IPlatformServices& platformServices,
					IResourceHandler& resourceHandler)
	: m_UIParent(uiParent),
	m_StyleSheet(styleSheet),
	m_ConsoleController(consoleController),
	m_SoundController(soundController),
	m_PlatformServices(platformServices),
	m_ResourceHandler(resourceHandler)
	{}
	
	TagReceiver*		getUIParent() { return m_UIParent; }
	const StyleSheet&	getStyleSheet() const { return m_StyleSheet; }
	ConsoleController&	getConsoleController() { return m_ConsoleController; }
	ISoundController&	getSoundController() { return m_SoundController; }
	IPlatformServices&	getPlatformServices() { return m_PlatformServices; }
	IResourceHandler&	getResourceHandler() { return m_ResourceHandler; }
	
private:
	TagReceiver*		m_UIParent;
	const StyleSheet&	m_StyleSheet;
	ConsoleController&	m_ConsoleController;
	ISoundController&	m_SoundController;
	IPlatformServices&	m_PlatformServices;
	IResourceHandler&	m_ResourceHandler;
};

}
