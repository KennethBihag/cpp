#include <iostream>

#define BOOST_TEST_MODULE Common Library Unit Test
#include "boost/test/included/unit_test.hpp"

using namespace std;

#include "permute.h"

constexpr bool BasicTest(){ return true; }

BOOST_AUTO_TEST_CASE(basic_test) {
    BOOST_TEST(BasicTest());
}

BOOST_AUTO_TEST_CASE(test_permute) {
    const int permuteData[] = { -2, -1, 0, 1, 2 };
	const int len = std::size(permuteData);
	int r = 0, c = 0;
	int *res = permute(permuteData, len, &r, &c);
	int orders = 0;
	for (int i = 0; i < r; ++i)
	{
		++orders;
		for (int j = 0; j < c; ++j)
			printf("%hd ", res[i * c + j]);
		printf("\n");
	}
	printf("%d orders\n", orders);
	free((void *)res);
}