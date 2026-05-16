#include <SFML/Graphics.hpp>
using namespace sf;
String strK(int code)
{
	switch (code)
	{
	case 0: return "A"; break;
	case 1: return "B"; break;
	case 2: return "C"; break;
	case 3: return "D"; break;
	case 4: return "E"; break;
	case 5: return "F"; break;
	case 6: return "G"; break;
	case 7: return "H"; break;
	case 8: return "I"; break;
	case 9: return "J"; break;
	case 10: return "K"; break;
	case 11: return "L"; break;
	case 12: return "M"; break;
	case 13: return "N"; break;
	case 14: return "O"; break;
	case 15: return "P"; break;
	case 16: return "Q"; break;
	case 17: return "R"; break;
	case 18: return "S"; break;
	case 19: return "T"; break;
	case 20: return "U"; break;
	case 21: return "V"; break;
	case 22: return "W"; break;
	case 23: return "X"; break;
	case 24: return "Y"; break;
	case 25: return "Z"; break;
	case 26: return "0"; break;
	case 27: return "1"; break;
	case 28: return "2"; break;
	case 29: return "3"; break;
	case 30: return "4"; break;
	case 31: return "5"; break;
	case 32: return "6"; break;
	case 33: return "7"; break;
	case 34: return "8"; break;
	case 35: return "9"; break;
	case 36: return "esc"; break;
	case 37: return "L ctrl"; break;
	case 38: return "L shift"; break;
	case 39: return "L alt"; break;
	case 40: return "L system"; break;
	case 41: return "R ctrl"; break;
	case 42: return "R shift"; break;
	case 43: return "R alt"; break;
	case 44: return "R system"; break;
	case 45: return "Menu"; break;
	case 46: return "["; break;
	case 47: return "]"; break;
	case 48: return ";"; break;
	case 49: return "<"; break;
	case 50: return ">"; break;
	case 51: return "'"; break;
	case 52: return "?"; break;
	case 53: return "|"; break;
	case 54: return "`"; break;
	case 55: return "="; break;
	case 56: return "_"; break;
	case 57: return "Space"; break;
	case 58: return "Enter"; break;
	case 59: return "Back space"; break;
	case 60: return "Tab"; break;
	case 61: return "pg up"; break;
	case 62: return "pg dn"; break;
	case 63: return "end"; break;
	case 64: return "home"; break;
	case 65: return "Ins"; break;
	case 66: return "del"; break;
	case 67: return "+"; break;
	case 68: return "-"; break;
	case 69: return "*"; break;
	case 70: return "/"; break;
	case 71: return "Left"; break;
	case 72: return "Right"; break;
	case 73: return "Up"; break;
	case 74: return "Down"; break;
	case 75: return "right 0"; break;
	case 76: return "right 1"; break;
	case 77: return "right 2"; break;
	case 78: return "right 3"; break;
	case 79: return "right 4"; break;
	case 80: return "right 5"; break;
	case 81: return "right 6"; break;
	case 82: return "right 7"; break;
	case 83: return "right 8"; break;
	case 84: return "right 9"; break;
	case 85: return "F1"; break;
	case 86: return "F2"; break;
	case 87: return "F3"; break;
	case 88: return "F4"; break;
	case 89: return "F5"; break;
	case 90: return "F6"; break;
	case 91: return "F7"; break;
	case 92: return "F8"; break;
	case 93: return "F9"; break;
	case 94: return "F10"; break;
	case 95: return "F11"; break;
	case 96: return "F12"; break;
	case 97: return "F13"; break;
	case 98: return "F14"; break;
	case 99: return "F15"; break;
	case 100: return "Pause/Break"; break;
	default: return "Unknown key"; break;
	}
}
String strM(int code)
{
	switch (code)
	{
	case 0: return "Left mouse button"; break;
	case 1: return "Right mouse button"; break;
	case 2: return "Middle mouse button"; break;
	case 3: return "Xbutton 1"; break;
	case 4: return "Xbutton 2"; break;
	default: return "Unknown button"; break;
	}
}