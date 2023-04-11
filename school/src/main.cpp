// amaris_sw_school.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "amaris.h"
#include "main_application.h"

#include <thread>
#include <chrono>

int main(int argc, char* argv[])
{
	amaris::sayHello();
	MainApplication app;
	// Init application
	app.init(argc, argv);
	// Run the application
	app.run();
	// Exit the application
	amaris::sayHello();
}