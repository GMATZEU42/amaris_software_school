#include "main_application.h"

#include "console.h"
#include "logger.h"
#include "prime.h"

#include <iostream>


// Public methods 
MainApplication::MainApplication()
{};

MainApplication::~MainApplication()
{};

void MainApplication::init(int argc, char* argv[])
{
	if (argc > 1)
	{
		consoleCommandInit(argc, argv);
	}
	else
	{
		configFileInit(argv[0]);
	}
}

void MainApplication::run()
{
	std::string inp = "";
	m_bRun = true;
	while (m_bRun)
	{
		inp = m_console.getInput();
		processInput(inp);
	}
}

// Private methods
void MainApplication::processInput(const std::string inp)
{
	if (inp == "c" || inp == "compute")
	{
		if (!m_pPrimer)
		{
			m_pPrimer = std::make_unique<prime::Primer>(m_loadPath);
		}
		m_computeThread = std::thread(&MainApplication::startPrimer, this);
	}
	else if (inp == "s" || inp == "stop")
	{
		if (m_pPrimer)
		{
			m_pPrimer->stopComputing();
		}
		if (m_computeThread.joinable())
		{
			m_computeThread.join();
		}
	}
	else if (inp == "e" || inp == "exit")
	{
		m_bRun = false;
		if (m_pPrimer)
		{
			m_pPrimer->stopComputing();
		}
		if (m_computeThread.joinable())
		{
			m_computeThread.join();
		}
	}
	else if (inp == "p" || inp == "print")
	{
		if (m_pPrimer)
		{
			auto primeList = m_pPrimer->getPrimeList();
			for (const auto p : primeList)
			{
				m_console.print(std::to_string(p), amaris::ConsoleColor::BLUE);
			}
		}
	}
	else if (inp == "pl" || inp == "print_last")
	{
		if (m_pPrimer)
		{
			m_console.print(std::to_string(m_pPrimer->getLast()), amaris::ConsoleColor::MAGENTA);
		}
	}
	else if (inp == "h" || inp == "help")
	{
		printHelp();
	}

}

void MainApplication::startPrimer()
{
	std::thread primeThd(&prime::Primer::compute, m_pPrimer.get(), prime::Primer::Algorithm::NAIVE, m_threshold);
	if (m_bDebugMode)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		while (m_pPrimer->isComputing())
		{
			std::this_thread::sleep_for(std::chrono::seconds(5));
			m_console.print("last prime computed: " + std::to_string(m_pPrimer->getLast()), amaris::ConsoleColor::BLUE);
		}
		m_console.print("Number of prime computed: " + std::to_string(m_pPrimer->getNumberOfPrime()), amaris::ConsoleColor::BLUE);
	}
	primeThd.join();
	m_pPrimer->save(m_savePath);
}

void MainApplication::configFileInit(std::filesystem::path configFilePath)
{
	// ToDo: read from config file all app settings.
}

void MainApplication::consoleCommandInit(int argc, char* argv[])
{
	for (auto i = 1U; i < argc; ++i)
	{
		std::string command{ argv[i] };
		if (command == "-h" || command == "-help")
		{
			printHelp();
		}
		else if (command == "-l" || command == "--load")
		{
			if (i + 1U < argc)
			{
				m_loadPath = argv[i + 1];
			}
		}
		else if (command == "-s" || command == "--save")
		{
			if (i + 1U < argc)
			{
				m_savePath = argv[i + 1];
			}
		}
		else if (command == "-t" || command == "--threshold")
		{
			if (i + 1U < argc)
			{
				m_threshold = std::atoi(argv[i + 1U]);
			}
		}
		else if (command == "-d" || command == "--debug")
		{
			m_bDebugMode = true;
		}
		else
		{
			printHelp();
		}
	}
}

void MainApplication::printHelp()
{
	std::string helpString =
	{
		"Hello everyone, this is an application that calculate prime numbers.\n"
		"[-h | --help]\t print an usage message\n"
		"[-l | --load <path>]\t set the path where to load primes\n"
		"[-s | --save <path>]\t set the path where to save primes\n"
		"[-t | --threshold <number>]\t set the when to stop the computation\n"
		"[-d | --debug]\t set debug mode while computing\n"
		"During the computation there are these commands avaible:\n"
		"[c | compute]\t to start the computation\n"
		"[s | stop]\t to stop the computation immediately\n"
		"[e | exit]\t to exit the application\n"
		"[h | help]\t to print the help menu\n"
	};
	m_console.print(helpString, amaris::ConsoleColor::YELLOW);
}
