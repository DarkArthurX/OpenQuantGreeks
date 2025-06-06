#include <catch2/catch_all.hpp>
#include "diffs.h"
#include "Greeks.h"
#include "math/maths.h"

using namespace GreeksCalculator;

TEST_CASE("Numerical Differentiation", "[numerical]") {
    double S = 100.0, K = 100.0, T = 1.0, r = 0.05, sigma = 0.2, q = 0.0;
    double tol = 1e-4; 

    SECTION("Numerical Delta vs Analytical") {
        double num_delta = numerical_delta(true, S, K, T, r, sigma, q);
        double ana_delta = calculate_delta(true, S, K, T, r, sigma, q);
        REQUIRE(std::abs(num_delta - ana_delta) < tol);
    }

    SECTION("Central Difference Accuracy") {
        auto f = [](double x) { return x * x; }; // f(x) = x^2, f'(x) = 2x
        double x = 2.0;
        double deriv = central_difference(f, x);
        REQUIRE(std::abs(deriv - 4.0) < tol);
    }

    SECTION("Mixed Partial Derivative") {
        auto f = [](double x, double y) { return x * y; }; // f(x,y) = xy, ∂²f/∂x∂y = 1
        double deriv = mixed_partial(f, 1.0, 1.0);
        REQUIRE(std::abs(deriv - 1.0) < tol);
    }
}