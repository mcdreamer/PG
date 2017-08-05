#pragma once

#include <SFML/Window.hpp>

#include "PG/core/KeyCode.h"

namespace PG {
namespace Internal {
namespace KeyCodeUtils {

//--------------------------------------------------------
KeyCode getKeyCode(const sf::Keyboard::Key& key)
{
	switch (key)
	{
	case sf::Keyboard::Escape: return KeyCode::kEscape;
	case sf::Keyboard::BackSpace: return KeyCode::kBackspace;
	case sf::Keyboard::Space: return KeyCode::kSpace;
	case sf::Keyboard::Return: return KeyCode::kEnter;

	case sf::Keyboard::Up: return KeyCode::kUp;
	case sf::Keyboard::Down: return KeyCode::kDown;
	case sf::Keyboard::Left: return KeyCode::kLeft;
	case sf::Keyboard::Right: return KeyCode::kRight;
		
	case sf::Keyboard::A: return KeyCode::kA;
	case sf::Keyboard::B: return KeyCode::kB;
	case sf::Keyboard::C: return KeyCode::kC;
	case sf::Keyboard::D: return KeyCode::kD;
	case sf::Keyboard::E: return KeyCode::kE;
	case sf::Keyboard::F: return KeyCode::kF;
	case sf::Keyboard::G: return KeyCode::kG;
	case sf::Keyboard::H: return KeyCode::kH;
	case sf::Keyboard::I: return KeyCode::kI;
	case sf::Keyboard::J: return KeyCode::kJ;
	case sf::Keyboard::K: return KeyCode::kK;
	case sf::Keyboard::L: return KeyCode::kL;
	case sf::Keyboard::M: return KeyCode::kM;
	case sf::Keyboard::N: return KeyCode::kN;
	case sf::Keyboard::O: return KeyCode::kO;
	case sf::Keyboard::P: return KeyCode::kP;
	case sf::Keyboard::Q: return KeyCode::kQ;
	case sf::Keyboard::R: return KeyCode::kR;
	case sf::Keyboard::S: return KeyCode::kS;
	case sf::Keyboard::T: return KeyCode::kT;
	case sf::Keyboard::U: return KeyCode::kU;
	case sf::Keyboard::V: return KeyCode::kV;
	case sf::Keyboard::W: return KeyCode::kW;
	case sf::Keyboard::X: return KeyCode::kX;
	case sf::Keyboard::Y: return KeyCode::kY;
	case sf::Keyboard::Z: return KeyCode::kZ;

	default:
		return KeyCode::kNone;
	}
}

}
}
}
