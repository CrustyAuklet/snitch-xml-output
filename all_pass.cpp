#include <testing.hpp>

TEST_CASE("requires will pass", "[testing]") {
    REQUIRE(true);
}

TEST_CASE("Nested checks", "[testing]") {
    REQUIRE(true);

    SECTION("Section1") {
        CHECK(true);
        SECTION("Section1.1") {
            CHECK(true);
        }
    }

    REQUIRE(true);
}

TEST_CASE("Static Checks", "[testing]") {
    STATIC_CHECK(true);
    STATIC_REQUIRE(true);
}

TEST_CASE("with captures", "[testing]") {
    int x = 2;
    int y = 5;
    CAPTURE(x, y);
    CHECK((x*y == 10));
}

TEST_CASE("sections with captures", "[testing]") {

    SECTION("Some Section") {
        int x = 2;
        int y = 5;
        CAPTURE(x, y);
        CHECK((x * y == 10));
    }
}

TEST_CASE("test should skip", "[testing]") {
    SKIP("This test is skippable");
}
