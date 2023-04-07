#include "gtest/gtest.h"

#include "prime.cpp"

TEST(Prime_Test_Suite, Test_Prime_Until20)
{
	EXPECT_TRUE(prime::isPrime(2));
	EXPECT_TRUE(prime::isPrime(3));
	EXPECT_TRUE(prime::isPrime(5));
	EXPECT_TRUE(prime::isPrime(7));
	EXPECT_TRUE(prime::isPrime(11));
	EXPECT_TRUE(prime::isPrime(13));
	EXPECT_TRUE(prime::isPrime(17));
	EXPECT_TRUE(prime::isPrime(19));	
}

TEST(Prime_Test_Suite, Test_Not_Prime_Until20)
{
	EXPECT_FALSE(prime::isPrime(4));
	EXPECT_FALSE(prime::isPrime(6));
	EXPECT_FALSE(prime::isPrime(8));
	EXPECT_FALSE(prime::isPrime(9));
	EXPECT_FALSE(prime::isPrime(10));
	EXPECT_FALSE(prime::isPrime(12));
	EXPECT_FALSE(prime::isPrime(14));
	EXPECT_FALSE(prime::isPrime(15));
	EXPECT_FALSE(prime::isPrime(16));
	EXPECT_FALSE(prime::isPrime(18));
}

TEST(Prime_Test_Suite, Test_Save_Load)
{
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
