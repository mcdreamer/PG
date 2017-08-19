#include "PG/internal/sound/SFMLSoundController.h"
#include "PG/io/IResourceHandler.h"
#include "PG/sound/Sound.h"
#include "PG/sound/SoundID.h"
#include "PG/sound/ISoundController.h"

#include <iostream>
#include <map>
#include <array>
#include <random>

#include <SFML/Audio.hpp>

namespace PG {
namespace Internal {

//--------------------------------------------------------
class SFMLSoundController::Impl
{
	//--------------------------------------------------------
	struct SoundAndBuffer
	{
		sf::SoundBuffer*	buffer;
		Sound				sound;
	};

	static const size_t kMaxNumSounds = 30;

public:
	//--------------------------------------------------------
	Impl(IResourceHandler& resourceHandler)
	: m_NthSound(0),
	m_NextID(0),
	m_ResourceHandler(resourceHandler)
	{}
	
	//--------------------------------------------------------
	SoundID registerSound(const Sound& sound)
	{
		const auto soundPath = m_ResourceHandler.getResourcePath(sound.resourceName, "wav");
		
		sf::SoundBuffer* buffer = getOrLoadBufferForPath(soundPath);
		if (!buffer)
		{
			std::cerr << "Failed to load sound " << soundPath << std::endl;
			
			return SoundID();
		}
		
		const SoundID soundID(m_NextID++);
		m_Sounds[soundID] = SoundAndBuffer { buffer, sound };

		return soundID;
	}
	
	//--------------------------------------------------------
	void playSound(const SoundID& soundID)
	{
		auto soundIt = m_Sounds.find(soundID);
		if (soundIt != m_Sounds.end())
		{
			std::random_device r;
			std::default_random_engine randomEngine(r());
			std::uniform_real_distribution<float> uniformDist(0.0, 1.0);

			const auto& pgSound = soundIt->second.sound;
			
			playBuffer(*soundIt->second.buffer,
					   getValueForRange(pgSound.pitchRange, uniformDist(randomEngine)),
					   getValueForRange(pgSound.volumeRange, uniformDist(randomEngine)));
		}
	}

private:
	std::array<sf::Sound, kMaxNumSounds>	m_PlayingSounds;
	size_t									m_NthSound;
	std::map<SoundID, SoundAndBuffer>		m_Sounds;
	std::map<std::string, sf::SoundBuffer>	m_SoundBuffers;
	int										m_NextID;
	
	IResourceHandler&						m_ResourceHandler;
	
	//--------------------------------------------------------
	sf::SoundBuffer* getOrLoadBufferForPath(const std::string& soundPath)
	{
		auto bufferIt = m_SoundBuffers.find(soundPath);
		if (bufferIt == m_SoundBuffers.end())
		{
			auto& buffer = m_SoundBuffers[soundPath];
			if (!buffer.loadFromFile(soundPath))
			{
				return nullptr;
			}
			
			return &buffer;
		}

		return &bufferIt->second;
	}
	
	//--------------------------------------------------------
	float getValueForRange(const ValueRange<float>& range, const float& rangePercent) const
	{
		return range.start + ((float)range.size() * rangePercent);
	}
	
	//--------------------------------------------------------
	void playBuffer(sf::SoundBuffer& buffer, const float pitch, const float volume)
	{
		auto& sound = m_PlayingSounds[m_NthSound];
		m_NthSound = (m_NthSound + 1) % kMaxNumSounds;
		
		sound = sf::Sound();
		
		sound.setBuffer(buffer);
		sound.setPitch(pitch);
		sound.setVolume(volume);
		
		sound.play();
	}
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
