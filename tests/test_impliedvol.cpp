#include <catch2/catch_all.hpp>
#include "bsm/impliedvol.h"
#include "bsm/price.h"
#include "math/maths.h"

using namespace GreeksCalculator;

TEST_CASE("Implied Volatility Solver", "[impliedvol]") {
    double S = 100.0, K = 100.0, T = 1.0, r = 0.05, q = 0.0;
    double tol = 1e-6;

    SECTION("Solve for known volatility") {
        double market_price = bsm_price(true, S, K, T, r, 0.2, q);
        double iv = calculate_implied_volatility(true, S, K, T, r, market_price, q);
        REQUIRE(std::abs(iv - 0.2) < tol);
    }

    SECTION("Non-convergence handling") {
        double invalid_price = 0.0; 
        REQUIRE_THROWS_AS(calculate_implied_volatility(true, S, K, T, r, invalid_price, q), std::invalid_argument);
    }

    SECTION("Edge case: low volatility") {
        double market_price = bsm_price(true, S, K, T, r, 0.01, q);
        double iv = calculate_implied_volatility(true, S, K, T, r, market_price, q);
        REQUIRE(std::abs(iv - 0.011256) < tol);
    }
}