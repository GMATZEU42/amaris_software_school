#pragma once

#include "console.h"
#include "windows.h"

namespace amaris
{
	void Console::changeColor(ConsoleColor color)
	{
		WORD c = 0U;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		switch (color)
		{
		case amaris::ConsoleColor::DEFAULT:
			break;
		case amaris::ConsoleColor::NATIVE:
			c = 7U;
			break;
		case amaris::ConsoleColor::BLUE:
			c = 9U;
			break;
		case amaris::ConsoleColor::RED:
			c = 12U;
			break;
		case amaris::ConsoleColor::GREEN:
			c = 10U;
			break;
		case amaris::ConsoleColor::YELLOW:
			c = 14U;
			break;
		default:
			break;
		}

		SetConsoleTextAttribute(hConsole, c);
	}
}