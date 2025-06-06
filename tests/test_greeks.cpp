#include <catch2/catch_all.hpp>
#include "bsm/full.h"
#include "math/maths.h"

using namespace GreeksCalculator;

TEST_CASE("Greeks Calculations", "[greeks]") {
    double S = 100.0, K = 100.0, T = 1.0, r = 0.05, sigma = 0.2, q = 0.02;
    double tol = 1e-6;

    Greeks g_call = bsm_full(true, S, K, T, r, sigma, q);
    Greeks g_put = bsm_full(false, S, K, T, r, sigma, q);
    
    // Test intraday scaling (no time scaling)
    Greeks g_intraday = calculate_all(true, S, K, T, r, sigma, q, ScalingParams::intraday());
    
    // Test no scaling at all
    Greeks g_unscaled = calculate_all(true, S, K, T, r, sigma, q, ScalingParams::no_scaling());

    SECTION("First Order Greeks - Call") {
        REQUIRE(std::abs(g_call.delta - 0.039851) < tol); // Current delta
        REQUIRE(std::abs(g_call.vega - 0.39908) < tol); // Scaled vega, per 1% change
        REQUIRE(std::abs(g_call.theta - (-0.012787)) < tol); // Scaled theta, daily
        REQUIRE(std::abs(g_call.rho - 0.454568) < tol); // Scaled rho, per 1% change
        REQUIRE(std::abs(g_call.epsilon - (-0.495160)) < tol); // Scaled epsilon, per 1% change
        REQUIRE(is_valid(g_call.lambda));
    }

    SECTION("First Order Greeks - Put") {
        REQUIRE(std::abs(g_put.delta - (-0.037652)) < tol); // Current delta
        REQUIRE(std::abs(g_put.vega - 0.39908) < tol); // Scaled vega, same for call/put
        REQUIRE(std::abs(g_put.theta - (-0.007374)) < tol); // Scaled theta, daily
        REQUIRE(std::abs(g_put.rho - (-0.443406)) < tol); // Scaled rho
        REQUIRE(std::abs(g_put.epsilon - 0.462762) < tol); // Scaled epsilon
        REQUIRE(is_valid(g_put.lambda));
    }

    SECTION("Second Order Greeks") {
        REQUIRE(std::abs(g_call.gamma - 0.0001506) < tol); // Current gamma
        REQUIRE(std::abs(g_call.vanna - (-0.071913)) < tol); // Scaled vanna
        REQUIRE(std::abs(g_call.volga - 0.998698) < tol); // Scaled volga
        REQUIRE(is_valid(g_call.charm));
        REQUIRE(is_valid(g_call.veta));
        REQUIRE(is_valid(g_call.vera));
        REQUIRE(is_valid(g_call.dual_rho));
    }

    SECTION("Higher-Order Greeks Stability") {
        // Test for T > 5/365 and sigma > 0.15
        Greeks g_high = bsm_full(true, S, K, 0.1, r, 0.3, q);
        REQUIRE(is_valid(g_high.pounce));
        REQUIRE(is_valid(g_high.hexema));
        REQUIRE(is_valid(g_high.mixed6th));

        // Test for small T and sigma
        Greeks g_low = bsm_full(true, S, K, 1.0/365.0, r, 0.05, q);
        REQUIRE(!is_valid(g_low.snap));
        REQUIRE(!is_valid(g_low.jounce));
        REQUIRE(!is_valid(g_low.pounce));
    }
    
    SECTION("Scaling Behavior") {
        // Test that intraday theta equals standard theta * 365
        REQUIRE(std::abs(g_intraday.theta - g_call.theta * 365.0) < tol);
        
        // Test that unscaled vega equals standard vega * 100
        REQUIRE(std::abs(g_unscaled.vega - g_call.vega * 100.0) < tol);
        
        // Test that unscaled rho equals standard rho * 100  
        REQUIRE(std::abs(g_unscaled.rho - g_call.rho * 100.0) < tol);
        
        // Test that intraday and standard Greeks have same delta (no scaling)
        REQUIRE(std::abs(g_intraday.delta - g_call.delta) < tol);
    }
}