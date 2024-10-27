// tests/sorting_tests.cpp
#include <gtest/gtest.h>
#include <vector>

template<typename T>
void swap(T& a, T& b) noexcept
{
	T temp = a;
	a = b;
	b = temp;
}

template<typename T>
void bubble_sort(std::vector<T>& in)
{
	for (size_t i = 0; i < in.size(); ++i)
	{
		for (size_t j = 0; j < in.size() - 1; ++j)
		{
			if (in[j] > in[j + 1])
			{
				swap(in[j], in[j + 1]);
			}
		}
	}
}


TEST(BubbleSortTest, CorrectlySortsVector) {
	std::vector input = {5, 2, 8, 1, 9};
	std::vector expected = {1, 2, 5, 8, 9};

	bubble_sort(input);
	
	EXPECT_EQ(input, expected);
}

TEST(BubbleSortTest, HandlesEmptyVector) {
	std::vector<int> input = {};
	std::vector<int> expected = {};

	bubble_sort(input);
	
	EXPECT_EQ(input, expected);
}

TEST(BubbleSortTest, HandlesSingleElement) {
	std::vector input = {1};
	std::vector expected = {1};

	bubble_sort(input);

	EXPECT_EQ(input, expected);
}