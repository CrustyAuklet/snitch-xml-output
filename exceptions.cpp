#include <testing.hpp>
#include <stdexcept>


int sum(int a, int b, bool will_throw = false) {
    if (will_throw) {
        throw std::runtime_error("throw!");
    }
    return a+b;
}

TEST_CASE("simple throwing test", "[testing]") {
    REQUIRE(sum(1,2) == 3);
    REQUIRE(sum(1,2,true) == 3);
}

TEST_CASE("Throw within one section", "[testing]") {
    REQUIRE(sum(1,2) == 3);

    SECTION("Throws in here") {
        REQUIRE(sum(1, 2, true) == 3);
    }
}

TEST_CASE("Throws in a nested section", "[testing]") {
    REQUIRE(true);

    SECTION("Section1") {
        CHECK(true);
        SECTION("Section1.1") {
            CHECK(sum(1, 2, true) == 3);
        }
    }

    REQUIRE(true);
}

TEST_CASE("with captures", "[testing]") {
    int x = 2;
    int y = 5;
    CAPTURE(x, y);
    CHECK(sum(x, y, true) == 7);
}

TEST_CASE("sections with captures", "[testing]") {

    SECTION("Some Section") {
        int x = 2;
        int y = 5;
        CAPTURE(x, y);
        CHECK(sum(x, y, true) == 7);
    }
}
