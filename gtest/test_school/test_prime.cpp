#include "gtest/gtest.h"

#include "prime.cpp"

#include <filesystem>

TEST(Prime_Test_Suite, Test_Save_Load)
{
	auto defaultDir = std::filesystem::current_path() / std::filesystem::path("prime.txt");
	if (std::filesystem::exists(defaultDir))
	{
		std::filesystem::remove(defaultDir);
	}
	{
		prime::Primer primer;
		primer.compute(prime::Primer::Algorithm::NAIVE, 10U);
		primer.save();
	}
	{
		prime::Primer primer;
		primer.load();
		GTEST_ASSERT_EQ(primer.getLast(), 7U);
		primer.compute(prime::Primer::Algorithm::NAIVE, 20U);
		primer.save("C:/temp/prime.txt");
	}
	{
		prime::Primer primer("C:/temp/prime.txt");
		GTEST_ASSERT_EQ(primer.getLast(), 19U);
	}
	std::filesystem::remove(std::filesystem::path(std::filesystem::current_path() / std::filesystem::path("prime.txt")));
	std::filesystem::remove("C:/temp/prime.txt");
}
