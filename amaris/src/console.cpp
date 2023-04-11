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
		std::lock_guard<std::mutex> lock(m_consoleMutex);
		if (color != ConsoleColor::DEFAULT)
		{
			changeColor(color);
		}
		if (m_bAutoEndl)
		{
			std::cout << m_prompt << s << std::endl;
		}
		else
		{
			std::cout << m_prompt << s;
		}
		changeColor(m_color);
	}


	std::string Console::getInput(ConsoleColor color)
	{
		printPrompt(color);
		std::string inp{};
		std::getline(std::cin, inp);
		return inp;
	}

	// private methods
	void Console::printPrompt(ConsoleColor color)
	{
		std::lock_guard<std::mutex> lock(m_consoleMutex);
		if (color != ConsoleColor::DEFAULT)
		{
			changeColor(color);
		}
		std::cout << m_prompt;
		changeColor(m_color);
	}
}