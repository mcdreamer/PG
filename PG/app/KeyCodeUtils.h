#pragma once

#include <string>

namespace PG {

enum class KeyCode;

namespace KeyCodeUtils {

void addCharacterForKeyCode(const PG::KeyCode& code, std::string& str);

}
}
