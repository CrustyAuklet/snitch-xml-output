#include <testing.hpp>

TEST_CASE("test should fail - require", "[testing]") {
    CHECK(false);
}

TEST_CASE("test should fail - check", "[testing]") {
    CHECK(true);
    CHECK(true);
    CHECK(false);
}

TEST_CASE("test should fail with capture", "[testing]") {
    int x = 2;
    int y = 5;
    CAPTURE(x, y);
    CHECK((x*y == 4));
}

TEST_CASE("test should skip", "[testing]") {
    SKIP("This test is skippable");
}
