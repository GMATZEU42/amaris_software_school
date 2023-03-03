#include "console.h"

#include <iostream>

#ifdef _WIN32
#include "console_win.h"
#else
#include "console_linux.h"
#endif

namespace amaris
{
	void Console::print(std::string s, ConsoleColor color)
	{
		if (color != ConsoleColor::DEFAULT)
		{
			changeColor(color);
		}
		std::cout << s << std::endl;
		changeColor(m_color);
	}
}