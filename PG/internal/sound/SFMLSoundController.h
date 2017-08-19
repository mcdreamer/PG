#pragma once

#include "PG/sound/ISoundController.h"

#include <memory>

namespace PG {

class IResourceHandler;

namespace Internal {

//--------------------------------------------------------
class SFMLSoundController : public ISoundController
{
	class Impl;

public:
	SFMLSoundController(IResourceHandler& resourceHandler);
	~SFMLSoundController();
	
	virtual SoundID	registerSound(const Sound& sound) override;
	virtual void	playSound(const SoundID& soundID) override;
	
private:
	std::unique_ptr<Impl>	m_Impl;
};

}
}
