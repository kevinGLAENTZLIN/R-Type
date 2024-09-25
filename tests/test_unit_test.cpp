#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("Example test") {
    int a = 5;
    int b = 5;
    CHECK(a == b);
}
