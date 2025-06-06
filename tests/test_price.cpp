#include <catch2/catch_all.hpp>
#include "bsm/price.h"
#include "bsm/validation.h"
#include "math/maths.h"

using namespace GreeksCalculator;

TEST_CASE("Black-Scholes-Merton Pricing", "[price]") {
    double S = 100.0, K = 100.0, T = 1.0, r = 0.05, sigma = 0.2, q = 0.0;
    double tol = 1e-6;

    SECTION("Call option price") {
        double price = bsm_price(true, S, K, T, r, sigma, q);
        REQUIRE(std::abs(price - 2.485016) < tol);
    }

    SECTION("Put option price") {
        double price = bsm_price(false, S, K, T, r, sigma, q);
        REQUIRE(std::abs(price - 2.293892) < tol);
    }

    SECTION("Put-call parity") {
        double call_price = bsm_price(true, S, K, T, r, sigma, q);
        double put_price = bsm_price(false, S, K, T, r, sigma, q);
        double lhs = call_price - put_price;
        double rhs = S - K * safe_exp(-r * T);
        REQUIRE(std::abs(lhs - rhs) < tol);
    }

    SECTION("Invalid inputs") {
        REQUIRE_THROWS_AS(bsm_price(true, -100.0, K, T, r, sigma, q), std::invalid_argument);
        REQUIRE_THROWS_AS(bsm_price(true, S, K, -1.0, r, sigma, q), std::invalid_argument);
        REQUIRE_THROWS_AS(bsm_price(true, S, K, T, r, -0.1, q), std::invalid_argument);
    }
}