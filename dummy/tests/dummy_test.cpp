#include "catch2/catch.hpp"

#include "gslam/dummy.h"

CATCH_TEST_CASE("dummy() returns 42", "") {
  CATCH_REQUIRE(gslam::dummy() == 42);
}
