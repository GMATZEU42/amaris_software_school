#include "logger.h"

namespace amaris
{	
	Logger::Logger(LoggerType type) 
	{
		switch (type)
		{
		case amaris::LoggerType::FILE:
			m_pLogger = std::make_unique<LoggerFile>();
			break;
		case amaris::LoggerType::CONSOLE:
			m_pLogger = std::make_unique<LoggerConsole>();
			break;
		default:
			break;
		}		
	}	

	void LoggerFile::log(std::string s)
	{
		//ToDo
	}

	void LoggerConsole::log(std::string s)
	{
		//ToDo
	}
}