#include "gtest/gtest.h"

#include "console.h"

#include <fstream>
#include <filesystem>


class Console_Test_Suite : public ::testing::Test
{
protected:
	//void SetUp() override { };

	//void TearDown() override { };	
};


TEST_F(Console_Test_Suite, Test_Ctor)
{
	auto console = amaris::Console(amaris::ConsoleColor::BLUE);	
	console.print("Hello!");
}

TEST_F(Console_Test_Suite, Test_PrintAllCollor)
{
	auto console = amaris::Console();
	console.print("Blue", amaris::ConsoleColor::BLUE);
	console.print("Green", amaris::ConsoleColor::GREEN);
	console.print("Native", amaris::ConsoleColor::NATIVE);
	console.print("Red", amaris::ConsoleColor::RED);
	console.print("Yellow", amaris::ConsoleColor::YELLOW);
	console.print("DEFAULT", amaris::ConsoleColor::DEFAULT);
}
