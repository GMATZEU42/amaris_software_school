// amaris_sw_school.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "amaris.h"
#include "logger.h"
#include "prime.h"

#include <thread>
#include <chrono>

//using namespace std::chrono_literals;

int main()
{
	amaris::sayHello();
	prime::Primer primer;
	std::thread primeThd(&prime::Primer::run, &primer);
	//
	amaris::Logger logger = amaris::Logger(amaris::LoggerType::CONSOLE);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	while (primer.isRunning())
	{
		std::this_thread::sleep_for(std::chrono::seconds(5));
		logger.log(amaris::LogLevel::DEBUG, "last prime computed: " + std::to_string(primer.getLast()));
	}
	logger.log(amaris::LogLevel::INFO, "Number of prime computed: " + std::to_string(primer.getNumberOfPrime()));
	//
	primeThd.join();
	amaris::sayHello();
}