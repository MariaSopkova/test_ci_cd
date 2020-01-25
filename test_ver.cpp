#define BOOST_TEST_MODULE print_patch_test_module

#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(print_patch_test_module_suite)

BOOST_AUTO_TEST_CASE(print_patch_ver)
{
    BOOST_CHECK(patch() != 3);
}

BOOST_AUTO_TEST_SUITE_END()
