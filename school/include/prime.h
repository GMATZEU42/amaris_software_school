#pragma once

#include <filesystem>
#include <vector>
#include <mutex>

namespace prime
{
	using PrimeType = unsigned long long;
	class Primer
	{
	public:
		enum class Algorithm
		{
			NAIVE
		};

		Primer(std::filesystem::path strSave = std::filesystem::path());
		~Primer() {};
		void compute(Algorithm alg = Algorithm::NAIVE, PrimeType threshold = 0U);
		bool isComputing();
		void stopComputing() { m_run = false; }
		bool isPrime(PrimeType v);
		PrimeType getLast();
		const std::vector<PrimeType>& getPrimeList();
		void save(std::filesystem::path path = std::filesystem::path());
		void load(std::filesystem::path path = std::filesystem::path());
		inline size_t getNumberOfPrime() { return m_primeList.size(); }
	private:
		std::vector<PrimeType> m_primeList{ 2U };
		std::mutex m_primeListMutex;
		std::atomic<bool> m_run = false;
		//
		std::filesystem::path m_savedFile = std::filesystem::current_path() / std::filesystem::path("prime.txt");
		//
		void computeNaive(PrimeType threshold = 0U);
	};
}
