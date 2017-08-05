#pragma once

namespace PG {

enum class KeyCode
{
    kNone,
    kUp,
    kDown,
    kLeft,
    kRight,
    kMinus,
    kEquals,
    kLeftBrace,
    kRightBrace,
    k9,
    k0,
    kSpeechMark,
    kBackSlash,
	kTab,
	kBackspace,
    kEscape,
    kEnter,
	kSpace,

	kA,
	kB,
	kC,
	kD,
	kE,
	kF,
	kG,
	kH,
	kI,
	kJ,
	kK,
	kL,
	kM,
	kN,
	kO,
	kP,
	kQ,
	kR,
	kS,
	kT,
	kU,
	kV,
	kW,
	kX,
	kY,
	kZ
};

enum class KeyModifier
{
	kNone  = 0,
	kShift = 1 << 0,
	kCmd = 1 << 1,
};

}
