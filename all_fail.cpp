#include <testing.hpp>

TEST_CASE("require_true will fail", "[testing]") {
    REQUIRE_FALSE(true);
}

TEST_CASE("Nested failure", "[testing]") {
    REQUIRE(true);

    SECTION("Section1") {
        CHECK(true);
        SECTION("Section1.1") {
            CHECK(false);
        }
    }

    REQUIRE(true);
}

TEST_CASE("with captures", "[testing]") {
    int x = 2;
    int y = 5;
    CAPTURE(x, y);
    CHECK((x*y == 8));
}

TEST_CASE("sections with captures", "[testing]") {

    SECTION("Some Section") {
        int x = 2;
        int y = 5;
        CAPTURE(x, y);
        CHECK_FALSE((x * y == 10));
    }
}

TEST_CASE("test should skip", "[testing]") {
    SKIP("This test is skippable");
    REQUIRE_FALSE(true);
}
