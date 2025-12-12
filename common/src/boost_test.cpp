#include <pch.hpp>

#define BOOST_TEST_MODULE Common Library Unit Test
#ifdef USE_BOOST_DLL
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#else
#include <boost/test/included/unit_test.hpp>
#endif
#ifndef BOOST_TEST_MODULE
#include <boost/test/parameterized_test.hpp>
#endif
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include "permute.h"

using namespace std;
using namespace boost::unit_test;
namespace data = boost::unit_test::data;

int arr1[] = {5};
int arr2[] = {2,4,6};
int arr3[] = {-2,-10,0,2,10};
int arr4[] = {1,2,3,4,5,6,7};
#ifdef BOOST_TEST_MODULE
int gLens[] = {1,3,5,7};
int gOrders[] = {1, 6, 120, 5040};
int *gArrs[] = {arr1, arr2, arr3, arr4};
using gTypes = tuple<char, short, int, long, long long, float, double, string>;
#else
tuple<int, int*, int> gParamsPermute[] = {
    make_tuple(1, arr1, 1),
    make_tuple(3, arr2, 6),
    make_tuple(5, arr3, 120),
    make_tuple(7, arr4, 5040)
};
#endif

inline void TestPermute(int len, int *arr, int exp){
    int r=0, c=0;
    int *res = permute(arr, len, &r, &c);
    free((void *)res);
    BOOST_TEST(r == exp);
}

inline void BasicTest(){
    BOOST_TEST(true);
}

inline void TestPermuteInt(){
    const int permuteData[] = {-2, -1, 0, 1, 2};
    const int len = std::size(permuteData);
    int r = 0, c = 0;
    int *res = permute(permuteData, len, &r, &c);
    free((void *)res);
    BOOST_TEST(r == 120);
}

#ifdef BOOST_TEST_MODULE

BOOST_AUTO_TEST_CASE(basic_test){
    BasicTest();
}

BOOST_DATA_TEST_CASE(
  test_permute_dataset,
  data::make(gLens) ^ gArrs ^ gOrders,
  len, arr, exp){
    TestPermute(len, arr, exp);
}

BOOST_AUTO_TEST_SUITE(PermuteTestSuite)
BOOST_AUTO_TEST_CASE(test_permute_int){
    TestPermuteInt();
}
BOOST_AUTO_TEST_CASE_TEMPLATE(templated_test, T, gTypes){
    size_t typeSz = sizeof(T);
    BOOST_TEST(typeSz < 6ULL);
}
BOOST_AUTO_TEST_SUITE_END()

#else

void ParamsTestPermute(const tuple<int, int*, int>& params){
    int len = get<0>(params);
    int *arr = get<1>(params);
    int exp = get<2>(params);
    TestPermute(len, arr, exp);
}

test_suite *init_unit_test_suite(int, char**)
{
    cout << "Manual registration!\n";
    auto ts1 = BOOST_TEST_SUITE("PermuteTestParamSuite");
    auto ts2 = BOOST_TEST_SUITE("PermuteTestSuite");

    framework::master_test_suite().add(BOOST_TEST_CASE(&BasicTest));

    ts1->add(BOOST_PARAM_TEST_CASE(
      &ParamsTestPermute, gParamsPermute, gParamsPermute + 4));
    ts2->add(BOOST_TEST_CASE(&TestPermuteInt));

    framework::master_test_suite().add(ts1);
    framework::master_test_suite().add(ts2);

    return 0;
}

#ifdef USE_BOOST_DLL
bool MainHelper(){
    init_unit_test_suite(0, nullptr);
    return &framework::master_test_suite() != nullptr;
};

int main(int argc, char *argv[]){
    cout << "Linked with Boost::Test DLL\n";
    return unit_test_main(MainHelper, argc, argv);
}
#endif

#endif
