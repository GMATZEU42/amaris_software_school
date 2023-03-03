#include "logger.h"

#include <iostream>
#include <fstream>


namespace amaris
{	
	Logger::Logger(LoggerType type, std::filesystem::path filePath, std::string fileName, std::string fileLog)
	{
		switch (type)
		{
		case amaris::LoggerType::FILE:
			m_pLogger = std::make_unique<LoggerFile>(filePath, fileName, fileLog);
			break;
		case amaris::LoggerType::CONSOLE:
			m_pLogger = std::make_unique<LoggerConsole>();
			break;
		default:
			break;
		}		
	}	

	LoggerFile::LoggerFile(std::filesystem::path filePath, std::string fileName, std::string fileFormat)
	{
		m_File = (filePath / std::filesystem::path(fileName)).string() + std::filesystem::path("." + fileFormat).string();
		if (!std::filesystem::exists(filePath))
		{
			try
			{
				std::filesystem::create_directory(filePath);
			}
			catch (...)
			{
				std::string exceptionLog = "Exception in LoggerFile ctor: " + std::string(LoggerFileException(ExceptionType::CANNOT_CREATE_DIR).what());
				logException(exceptionLog);
				throw(LoggerFileException(ExceptionType::CANNOT_CREATE_DIR));
			}
		}
	}

	void LoggerFile::log(std::string s)
	{
		try
		{
			std::fstream file;
			file.open(m_File, std::fstream::out | std::fstream::app);
			if (file.is_open())
			{
				file << s << std::endl;
				file.close();
			}
			else
			{
				throw(LoggerFileException(ExceptionType::CANNOT_OPEN_FILE));
			}
		}
		catch (std::exception & e)
		{
			std::string exceptionLog = "Exception raised in LoggerFile::log - " + std::string(e.what());
			logException(exceptionLog);
		}
		catch (...)
		{
			// ops!
		}
	}

	void LoggerFile::logException(std::string e)
	{
		std::cout << e << std::endl;
		auto file = std::fstream((std::filesystem::current_path() / std::filesystem::path("error.log")).string(), std::ios_base::out);
		if (file.is_open())
		{
			file << e;
			file.close();
		}
	}

	void LoggerConsole::log(std::string s)
	{
		//ToDo
	}
}