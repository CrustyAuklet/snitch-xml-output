#pragma once
#if defined(TESTING_USE_CATCH2)
#    include <catch2/catch_test_macros.hpp> // IWYU pragma: export
#else // TESTING_USE_CATCH2
#    include <snitch/snitch.hpp> // IWYU pragma: export
#    include <span>
#    define STATIC_CHECK(...) CONSTEXPR_CHECK(__VA_ARGS__)
#    define STATIC_CHECK_FALSE(...) CONSTEXPR_CHECK_FALSE(__VA_ARGS__)
#    define STATIC_REQUIRE(...) CONSTEXPR_REQUIRE(__VA_ARGS__)
#    define STATIC_REQUIRE_FALSE(...) CONSTEXPR_REQUIRE_FALSE(__VA_ARGS__)
#endif // TESTING_USE_CATCH2