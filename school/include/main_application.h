#pragma once

#include "prime.h"
#include "console.h"

#include <filesystem>
#include <memory>

class MainApplication
{
public:
	MainApplication();
	~MainApplication();
	void init(int argc, char* argv[]);
	void run();
private:	// Methods
	void consoleCommandInit(int argc, char* argv[]);
	void configFileInit(std::filesystem::path configFilePath);
	void processInput(const std::string inp);
	void startPrimer();
	void printHelp();
	void printPrompt();
private:	// Fields
	std::unique_ptr<prime::Primer> m_pPrimer;
	std::thread m_computeThread;
	//
	amaris::Console m_console = amaris::Console(amaris::ConsoleColor::GREEN, ">> ", true);
	//
	std::filesystem::path m_savePath = std::filesystem::current_path() / std::filesystem::path("application.txt");
	std::filesystem::path m_loadPath = std::filesystem::current_path() / std::filesystem::path("application.txt");
	unsigned m_threshold = 0U;
	// 
	bool m_bRun = false;
	bool m_bDebugMode = false;


};
