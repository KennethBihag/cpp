#include <iostream>
#include <tuple>
#include <vector>

#ifdef USE_BOOST_DLL
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#else
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>
