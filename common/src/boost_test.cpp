#include <iostream>

#define BOOST_TEST_MODULE Common Library Unit Test
#include "boost/test/included/unit_test.hpp"

#include "tests.h"

using namespace std;

constexpr bool BasicTest(){ return true; }

BOOST_AUTO_TEST_CASE(basic_test) {
    BOOST_TEST(BasicTest());
}

BOOST_AUTO_TEST_CASE(test_permute) {
    int permuteData[] = {
        5,
        -2, -1, 0, 1, 2
    };
    BOOST_TEST(permute_test(permuteData) == nullptr);
}