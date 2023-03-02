#include "gtest/gtest.h"

#include "logger.h"

#include <fstream>
#include <filesystem>


class LoggerFile_Test_Suite : public ::testing::Test
{
protected:
	void SetUp() override
	{
		testStr = "quarantadue";
		logPath = std::filesystem::current_path().string();
		logName = "tmp";
		logFormat = "log";
	};

	bool findStrFromLog(std::string s)
	{
		std::string file = (logPath / std::filesystem::path(logName)).string() + std::filesystem::path("." + logFormat).string();
		auto fileStream = std::fstream(file, std::ios_base::in);
		std::string line{};
		bool bFound = false;
		if (fileStream.is_open())
		{
			while (std::getline(fileStream, line))
			{
				if (line.find(s) != std::string::npos)
				{
					bFound = true;
					break;
				}
			}
			fileStream.close();
		}
		return bFound;
	}

	std::string testStr;
	std::filesystem::path logPath; 
	std::string logName; 
	std::string logFormat;
	std::unique_ptr<amaris::Logger> testLogger;
};



TEST_F(LoggerFile_Test_Suite, TestLogCreation)
{
	//	Default case
	testLogger = std::make_unique<amaris::Logger>(amaris::LoggerType::FILE);
	testLogger->log(amaris::LogLevel::INFO, testStr);
	GTEST_ASSERT_TRUE(findStrFromLog(testStr));
}

TEST_F(LoggerFile_Test_Suite, TestLogCreationCustom)
{
	// Custom directory
	testStr = "quarantatre";
	logPath = std::filesystem::path("C:\\tmp");
	logName = std::string("customName");
	logFormat = std::string("customFormat");
	testLogger = std::make_unique<amaris::Logger>(amaris::LoggerType::FILE, logPath, logName, logFormat);
	testLogger->log(amaris::LogLevel::INFO, testStr);
	GTEST_ASSERT_TRUE(findStrFromLog(testStr));
}

TEST_F(LoggerFile_Test_Suite, TestLogInfo)
{
	testLogger = std::make_unique<amaris::Logger>(amaris::LoggerType::FILE);
	testLogger->log(amaris::LogLevel::INFO, testStr);
	GTEST_ASSERT_TRUE(findStrFromLog("INFO"));
}

TEST_F(LoggerFile_Test_Suite, TestLogError)
{
	testLogger = std::make_unique<amaris::Logger>(amaris::LoggerType::FILE);
	testLogger->log(amaris::LogLevel::ERROR, testStr);
	GTEST_ASSERT_TRUE(findStrFromLog("ERROR"));
}

TEST_F(LoggerFile_Test_Suite, TestLogDebug)
{
	testLogger = std::make_unique<amaris::Logger>(amaris::LoggerType::FILE);
	testLogger->log(amaris::LogLevel::DEBUG, testStr);
	GTEST_ASSERT_TRUE(findStrFromLog("DEBUG"));
}

TEST_F(LoggerFile_Test_Suite, TestLogWarning)
{
	testLogger = std::make_unique<amaris::Logger>(amaris::LoggerType::FILE);
	testLogger->log(amaris::LogLevel::WARNING, testStr);
	GTEST_ASSERT_TRUE(findStrFromLog("WARNING"));
}