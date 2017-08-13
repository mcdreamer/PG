#include "PG/app/KeyCodeUtils.h"
#include "PG/core/KeyCode.h"

namespace PG {
namespace KeyCodeUtils {

//--------------------------------------------------------
void addCharacterForKeyCode(const PG::KeyCode& code, std::string& str)
{
	switch (code)
	{
		case PG::KeyCode::kA: str += "a"; break;
		case PG::KeyCode::kB: str += "b"; break;
		case PG::KeyCode::kC: str += "c"; break;
		case PG::KeyCode::kD: str += "d"; break;
		case PG::KeyCode::kE: str += "e"; break;
		case PG::KeyCode::kF: str += "f"; break;
		case PG::KeyCode::kG: str += "g"; break;
		case PG::KeyCode::kH: str += "h"; break;
		case PG::KeyCode::kI: str += "i"; break;
		case PG::KeyCode::kJ: str += "j"; break;
		case PG::KeyCode::kK: str += "k"; break;
		case PG::KeyCode::kL: str += "l"; break;
		case PG::KeyCode::kM: str += "m"; break;
		case PG::KeyCode::kN: str += "n"; break;
		case PG::KeyCode::kO: str += "o"; break;
		case PG::KeyCode::kP: str += "p"; break;
		case PG::KeyCode::kQ: str += "q"; break;
		case PG::KeyCode::kR: str += "r"; break;
		case PG::KeyCode::kS: str += "s"; break;
		case PG::KeyCode::kT: str += "t"; break;
		case PG::KeyCode::kU: str += "u"; break;
		case PG::KeyCode::kV: str += "v"; break;
		case PG::KeyCode::kW: str += "w"; break;
		case PG::KeyCode::kX: str += "x"; break;
		case PG::KeyCode::kY: str += "y"; break;
		case PG::KeyCode::kZ: str += "z"; break;
		case PG::KeyCode::kSpace: str += " "; break;
			
		default:
			break;
	}
}

}
}
