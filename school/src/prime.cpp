#include "prime.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <thread>

namespace prime
{
	Primer::Primer(std::filesystem::path saveFile)
	{
		load(saveFile);
	}

	void Primer::compute(Algorithm alg, PrimeType threshold)
	{
		//
		if (m_primeList.back() < threshold)
		{
			switch (alg)
			{
			case prime::Primer::Algorithm::NAIVE:
				computeNaive(threshold);
				break;
			default:
				break;
			}
		}
	}

	PrimeType Primer::getLast()
	{
		std::lock_guard<std::mutex> lock(m_primeListMutex);
		return m_primeList.back();
	}

	const std::vector<PrimeType>& Primer::getPrimeList()
	{
		std::lock_guard<std::mutex> lock(m_primeListMutex);
		return m_primeList;
	}

	bool Primer::isComputing()
	{
		return m_run;
	}

	bool Primer::isPrime(PrimeType value)
	{
		return (std::find(begin(m_primeList), end(m_primeList), value) != end(m_primeList));
	}

	void Primer::save(std::filesystem::path filePath)
	{
		if (!m_run)
		{
			std::string pathStr = filePath.empty() ? m_savedFile.string() : filePath.string();
			std::fstream stream = std::fstream(pathStr, std::fstream::out | std::fstream::app);
			if (stream.is_open())
			{
				for (auto p : m_primeList)
				{
					stream << p << std::endl;

				}
				stream.close();
			}
		}
	}

	void Primer::load(std::filesystem::path filePath)
	{
		std::string pathStr = filePath.empty() ? m_savedFile.string() : filePath.string();
		std::fstream stream = std::fstream(pathStr, std::fstream::in);
		if (stream.is_open())
		{
			m_primeList.clear();
			std::string line;
			while (std::getline(stream, line))
			{
				PrimeType prime = std::atoll(line.c_str());
				if (prime > 0U)
				{
					m_primeList.push_back(prime);
				}
			}
		}
	}

	void Primer::computeNaive(PrimeType threshold)
	{
		m_run.store(true);
		bool bPrime;
		for (PrimeType n = m_primeList.back() + 1U; n < std::numeric_limits<PrimeType>::max() && m_run && n < threshold; ++n)
		{
			bPrime = true;
			for (const auto& prime : m_primeList)
			{
				if (prime <= n / 2 && n % prime == 0)
				{
					bPrime = false;
					break;
				}
			}
			if (bPrime)
			{
				std::lock_guard<std::mutex> lock(m_primeListMutex);
				m_primeList.emplace_back(n);
			}
		}
		m_run.store(false);
	}
}