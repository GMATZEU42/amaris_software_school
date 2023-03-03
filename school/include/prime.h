#pragma once

#include <vector>
#include <mutex>

namespace prime
{
	using PrimeType = unsigned short;
	class Primer
	{
	public:
		Primer() {};
		~Primer() {};
		void run();
		bool isRunning();
		bool isPrime(PrimeType v);
		PrimeType getLast();
		inline size_t getNumberOfPrime() { return m_primeList.size(); }
	private:
		std::vector<PrimeType> m_primeList{};
		std::mutex m_primeListMutex;
		std::atomic<bool> m_run = false;
	};

	bool isPrime(PrimeType v);
}
