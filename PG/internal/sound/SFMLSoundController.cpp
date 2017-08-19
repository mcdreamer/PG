#include "PG/internal/sound/SFMLSoundController.h"
#include "PG/io/IResourceHandler.h"
#include "PG/sound/Sound.h"
#include "PG/sound/SoundID.h"
#include "PG/sound/ISoundController.h"

#include <iostream>
#include <map>
#include <vector>

#include <SFML/Audio.hpp>

namespace PG {
namespace Internal {

//--------------------------------------------------------
class SFMLSoundController::Impl
{
public:
	Impl(IResourceHandler& resourceHandler)
	: m_NextID(0),
	m_ResourceHandler(resourceHandler)
	{}
	
	//--------------------------------------------------------
	SoundID registerSound(const Sound& sound)
	{
		auto soundPath = m_ResourceHandler.getResourcePath(sound.resourceName, "wav");
		
		const SoundID soundID(m_NextID++);
		
		auto& buffer = m_SoundBuffers[soundID];
		if (!buffer.loadFromFile(soundPath))
		{
			std::cerr << "Failed to load sound" << std::endl;
		}
		
		return soundID;
	}
	
	//--------------------------------------------------------
	void playSound(const SoundID& soundID)
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
	int									m_NextID;
	std::vector<sf::Sound>				m_Sounds;
	
	IResourceHandler&					m_ResourceHandler;
};

//--------------------------------------------------------
SFMLSoundController::SFMLSoundController(IResourceHandler& resourceHandler)
: m_Impl(new Impl(resourceHandler))
{}

//--------------------------------------------------------
SFMLSoundController::~SFMLSoundController()
{}

//--------------------------------------------------------
SoundID SFMLSoundController::registerSound(const Sound& sound)
{
	return m_Impl->registerSound(sound);
}

//--------------------------------------------------------
void SFMLSoundController::playSound(const SoundID& soundID)
{
	m_Impl->playSound(soundID);
}

}
}
