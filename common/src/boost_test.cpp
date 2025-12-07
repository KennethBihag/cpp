#include <iostream>

#include "boost/test/included/unit_test.hpp"

using namespace std;
using namespace boost::unit_test;

#include "permute.h"

constexpr bool BasicTest() { return true; }

#ifdef BOOST_TEST_MODULE
BOOST_AUTO_TEST_CASE(basic_test) {
    BOOST_TEST(BasicTest());
}
#endif

#ifdef BOOST_TEST_MODULE
BOOST_AUTO_TEST_CASE(test_permute)
#else
void test_permute()
#endif
{
    const int permuteData[] = {-2, -1, 0, 1, 2};
    const int len = std::size(permuteData);
    int r = 0, c = 0;
    int *res = permute(permuteData, len, &r, &c);
    int orders = 0;
    for (int i = 0; i < r; ++i)
    {
        ++orders;
        for (int j = 0; j < c; ++j)
            ;
        // printf("%hd ", res[i * c + j]);
        // printf("\n");
    }
    // printf("%d orders\n", orders);
    free((void *)res);
    BOOST_TEST(res);
}

#ifndef BOOST_TEST_MODULE
test_suite *init_unit_test_suite(int /*argc*/, char * /*argv*/[])
{
    cout << "Manual registration!\n";
    framework::master_test_suite().add(BOOST_TEST_CASE(&test_permute));
    framework::master_test_suite().add(BOOST_TEST_CASE(&BasicTest));
    return 0;
}
#endif