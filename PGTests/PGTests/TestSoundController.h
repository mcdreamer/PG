#pragma once

#include "PG/sound/ISoundController.h"
#include "PG/sound/SoundID.h"

//--------------------------------------------------------
class TestSoundController : public PG::ISoundController
{
public:
	virtual PG::SoundID	registerSound(const PG::Sound& sound) override { return PG::SoundID(0); }
	virtual void		playSound(const PG::SoundID& soundID) override {}
};
