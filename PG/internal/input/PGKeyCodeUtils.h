#pragma once

#include <SFML/Window.hpp>

#include "PG/core/PGKeyCode.h"

namespace PG {
namespace Internal {
namespace PGKeyCodeUtils {

//--------------------------------------------------------
PGKeyCode getPGKeyCode(const sf::Keyboard::Key& key)
{
	switch (key)
	{
	case sf::Keyboard::Escape:
		return PGKeyCodeEscape;

	case sf::Keyboard::Up:
		return PGKeyCodeUp;

	case sf::Keyboard::Down:
		return PGKeyCodeDown;

	case sf::Keyboard::Left:
		return PGKeyCodeLeft;

	case sf::Keyboard::Right:
		return PGKeyCodeRight;

	default:
		return PGKeyCodeNone;
	}
}

}
}
}
