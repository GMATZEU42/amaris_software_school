#pragma once

#include <string>
#include <memory>
#include <map>

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

	class Logger
	{
	public:
		explicit Logger(LoggerType type);
		~Logger();
		template <typename T> 
		void log(LogLevel lvl, T log)
		{
			m_pLogger->log(m_levelStringMap.at(level) + " " + std::to_string(log));
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

	class LoggerBase
	{
	public:
		LoggerBase() {};
		virtual ~LoggerBase() {};
		virtual void log(std::string log) = 0;

	};

	class LoggerFile : public LoggerBase
	{
	public:
		LoggerFile() {};
		~LoggerFile() {};
		void log(std::string log) override;
	};

	class LoggerConsole : public LoggerBase
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
}



