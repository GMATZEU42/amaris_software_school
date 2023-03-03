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

	void TearDown() override
	{
		auto filePath = (logPath / std::filesystem::path(logName + "." + logFormat));
		std::filesystem::remove(filePath);
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

	bool findStrFromLog(std::vector<std::string> vString)
	{
		bool bFound = true;
		for (auto s : vString)
		{
			bFound &= findStrFromLog(s);
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
	logName = std::string("TestLogCreationCustom");
	logFormat = std::string("customFormat");
	testLogger = std::make_unique<amaris::Logger>(logPath, logName, logFormat);
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

TEST_F(LoggerFile_Test_Suite, TestLogNumeric)
{
	testLogger = std::make_unique<amaris::Logger>(amaris::LoggerType::FILE);
	int int32 = 30;
	unsigned int uInt32 = 31U;
	float float32 = 3.14f;
	double double64 = 2.7183;
	testLogger->log(amaris::LogLevel::WARNING, int32);
	testLogger->log(amaris::LogLevel::WARNING, uInt32);
	testLogger->log(amaris::LogLevel::WARNING, float32);
	testLogger->log(amaris::LogLevel::WARNING, double64);
	GTEST_ASSERT_TRUE(findStrFromLog({ {"30"}, {"31"}, {"3.14"}, {"2.7183"} }));
}

TEST_F(LoggerFile_Test_Suite, TestLogInt)
{
	testLogger = std::make_unique<amaris::Logger>(amaris::LoggerType::FILE);
	testLogger->log(amaris::LogLevel::WARNING, 42);
	GTEST_ASSERT_TRUE(findStrFromLog("42"));
}

TEST_F(LoggerFile_Test_Suite, TestLogMoreLogs)
{
	testLogger = std::make_unique<amaris::Logger>(amaris::LoggerType::FILE);
	testLogger->log(amaris::LogLevel::WARNING, 42);
	testLogger->log(amaris::LogLevel::WARNING, 43);
	GTEST_ASSERT_TRUE(findStrFromLog({ {"42"}, {"43"} }));
}

// Test for LoggerConsole
TEST(LoggerConsole_Test_Suite, Test_Print)
{
	auto clogger = std::make_unique<amaris::Logger>(amaris::LoggerType::CONSOLE);
	clogger->log(amaris::LogLevel::INFO, "This is an info");
	clogger->log(amaris::LogLevel::WARNING, "This is a warning");
	clogger->log(amaris::LogLevel::DEBUG, "This is a debug info");
	clogger->log(amaris::LogLevel::ERROR, "This is an error");
}