#pragma once

namespace GreeksCalculator {
    double calculate_implied_volatility(bool call, double S, double K, double T, double r, double market_price, double q = 0.0, double tol = 1e-6, int max_iter = 100);
}