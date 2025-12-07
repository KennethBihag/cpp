#include <pch.hpp>
using namespace std;
using namespace boost::unit_test;
namespace data = boost::unit_test::data;

#include "permute.h"

int gLens[] = {1,3,5,7};
int arr1[] = {5};
int arr2[] = {2,4,6};
int arr3[] = {-2,-10,0,2,10};
int arr4[] = {1,2,3,4,5,6,7};
int *gArrs[] = {arr1, arr2, arr3, arr4};
int gOrders[] = {1, 6, 120, 5040};
BOOST_DATA_TEST_CASE(
    test_permute_dataset,
    data::make(gLens) ^ gArrs ^ gOrders,
    len, arr, exp)
{
    int r=0, c=0;
    int *res = permute(arr, len, &r, &c);
    free((void *)res);
    BOOST_TEST(r == exp);
}

#ifdef BOOST_TEST_MODULE
BOOST_AUTO_TEST_CASE(basic_test)
#else
void basic_test()
#endif
{
    BOOST_TEST(true);
}

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
    free((void *)res);
    BOOST_TEST(r == 120);
}

#ifndef BOOST_TEST_MODULE
test_suite *init_unit_test_suite(int /*argc*/, char * /*argv*/[])
{
    cout << "Manual registration!\n";
    framework::master_test_suite().add(BOOST_TEST_CASE(&basic_test));
    framework::master_test_suite().add(BOOST_TEST_CASE(&test_permute));
    return 0;
}
#endif