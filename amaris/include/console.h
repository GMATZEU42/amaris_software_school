#pragma once

#include "amaris.h"

#include <string>
#include <mutex>

namespace amaris
{
	enum class ConsoleColor 
	{
		DEFAULT,
		NATIVE,
		GREY,
		BLUE,
		GREEN,
		AZURE,
		RED,
		MAGENTA,
		YELLOW
	};	

	class AMARIS_API Console
	{
	public:
		Console(ConsoleColor c = ConsoleColor::NATIVE, std::string prompt = "", bool autoEndl = true) :
			m_color(c), m_prompt(prompt), m_bAutoEndl(autoEndl) { changeColor(m_color); };
		~Console() { changeColor(ConsoleColor::NATIVE); };
		void print(std::string s, ConsoleColor color = ConsoleColor::DEFAULT);
		std::string getInput(ConsoleColor color = ConsoleColor::DEFAULT);
	private:
		ConsoleColor m_color;
		bool m_bAutoEndl;
		std::string m_prompt = "";
		std::mutex m_consoleMutex;
		void printPrompt(ConsoleColor color = ConsoleColor::DEFAULT);
		void changeColor(ConsoleColor color);
	};
}
