#pragma once

#include "amaris.h"

#include <string>
#include <memory>
#include <map>
#include <filesystem>

namespace amaris
{
	enum class LoggerType : unsigned int
	{
		FILE = 0,
		CONSOLE = 1
	};

	enum class LogLevel : unsigned int
	{
		DEBUG = 1,
		INFO = 100,
		WARNING = 200,
		ERROR = 500
	};

	class LoggerBase;

	class AMARIS_API Logger
	{
	public:
		explicit Logger(LoggerType type, std::filesystem::path filePath = std::filesystem::current_path(), std::string fileName = "tmp", std::string fileLog = "log");
		~Logger() {};
		//
		template <typename T> 
		void log(LogLevel lvl, T log)
		{
			m_pLogger->log(m_levelStringMap.at(lvl) + " " + std::to_string(log));
		}
	private:
		std::unique_ptr<LoggerBase> m_pLogger;
		const std::map<LogLevel, std::string> m_levelStringMap{
			{LogLevel::DEBUG, "DEBUG"}, 
			{LogLevel::INFO, "INFO"}, 
			{LogLevel::WARNING, "WARNING"}, 
			{LogLevel::ERROR, "ERROR"} 
		};
	};

	class AMARIS_API LoggerBase
	{
	public:
		LoggerBase() {};
		virtual ~LoggerBase() {};
		virtual void log(std::string log) = 0;
	};


	class AMARIS_API LoggerFile : public LoggerBase
	{
		enum class ExceptionType
		{
			CANNOT_OPEN_FILE,
			CANNOT_CREATE_DIR
		};

		class LoggerFileException : public std::exception
		{	
		public:
			LoggerFileException(ExceptionType type) : m_type(type) {};
			char const* what() const override { return m_exceptionMap.at(m_type).c_str(); }
		private:
			const std::map<ExceptionType, std::string> m_exceptionMap{ 
				{ExceptionType::CANNOT_OPEN_FILE, "CANNOT_OPEN_FILE"},
				{ExceptionType::CANNOT_OPEN_FILE, "CANNOT_CREATE_DIR"}
			};
			ExceptionType m_type;
		};
	public:
		LoggerFile(std::filesystem::path filePath = std::filesystem::current_path(), std::string fileName = "tmp", std::string fileFormat = "log");
		~LoggerFile() {};
		void log(std::string log) override;
	private:
		std::string m_File;
	private:
		void logException(std::string e);
	};
	

	class AMARIS_API LoggerConsole : public LoggerBase
	{
	public:
		LoggerConsole() {};
		~LoggerConsole() {};
		void log(std::string log) override;
	private:
	};

	template <>
	void Logger::log(LogLevel level, std::string s)
	{
		m_pLogger->log(m_levelStringMap.at(level) + " " + s);
	}

	template <>
	void Logger::log(LogLevel level, char* s)
	{
		m_pLogger->log(m_levelStringMap.at(level) + " " + std::string(s));
	}
}



