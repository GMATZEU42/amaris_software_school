#include "prime.h"

#include <algorithm>

namespace prime
{
	bool isPrime(PrimeType value)
	{
		if(value < 2)
		{
			return false;
		}
		else
		{
			int d = 2;
			while (value % d != 0 && d <= value)
			{
				d++;
			}
			return (d == value);
		}
	}

	void Primer::run()
	{
		//
		m_run.store(true);
		bool bPrime;
		m_primeList.push_back(2U);
		for (PrimeType n = 3; n < std::numeric_limits<PrimeType>::max(); ++n)
		{
			bPrime = true;
			for (const auto& prime : m_primeList)
			{
				if (prime <= n/2 && n % prime == 0)
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

	PrimeType Primer::getLast()
	{
		std::lock_guard<std::mutex> lock(m_primeListMutex);
		return m_primeList.back();
	}

	bool Primer::isRunning()
	{
		return m_run;
	}

	bool Primer::isPrime(PrimeType value)
	{
		return (std::find(begin(m_primeList), end(m_primeList), value) != end(m_primeList));
	}
}