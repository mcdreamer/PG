#pragma once

namespace PG {

enum PGKeyCode
{
    PGKeyCodeNone,
    PGKeyCodeUp,
    PGKeyCodeDown,
    PGKeyCodeLeft,
    PGKeyCodeRight,
    PGKeyCodeMinus,
    PGKeyCodeEquals,
    PGKeyCodeD,
    PGKeyCodeLeftBrace,
    PGKeyCodeRightBrace,
    PGKeyCode9,
    PGKeyCode0,
    PGKeyCodeSpeechMark,
    PGKeyCodeBackSlash,
	PGKeyCodeTab,
	PGKeyCodeBackspace,
    PGKeyCodeEscape,
    PGKeyCodeEnter
};

enum PGKeyModifier
{
	PGKeyModifierNone  = 0,
	PGKeyModifierShift = 1 << 0,
	PGKeyModifierCmd = 1 << 1,
};

}
