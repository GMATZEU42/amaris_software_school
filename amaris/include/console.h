#pragma once

#include "amaris.h"

#include <string>

namespace amaris
{
	enum class ConsoleColor 
	{
		DEFAULT,
		NATIVE,
		BLUE,
		RED,
		GREEN,
		YELLOW
	};

	class AMARIS_API Console
	{
	public:
		Console(ConsoleColor c = ConsoleColor::NATIVE) : m_color(c){ changeColor(m_color); };
		~Console() { changeColor(ConsoleColor::NATIVE); };
		void print(std::string s, ConsoleColor color = ConsoleColor::DEFAULT);
		inline void setColor(ConsoleColor c) { m_color = c; }
	private:
		ConsoleColor m_color;
		void changeColor(ConsoleColor color);
	};
}
