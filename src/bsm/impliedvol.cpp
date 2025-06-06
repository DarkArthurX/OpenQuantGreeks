#include "bsm/impliedvol.h"
#include "bsm/validation.h"
#include "Greeks.h"
#include <stdexcept>
#include <cmath>

namespace GreeksCalculator {
    double calculate_implied_volatility(bool call, double S, double K, double T, double r, double market_price, double q, double tol, int max_iter) {
        validate_inputs(S, K, T, r, 0.1, q);
        if (market_price <= 0.0) {
            throw std::invalid_argument("Market price must be positive.");
        }

        double sigma = 0.2;
        for (int i = 0; i < max_iter; ++i) {
            double price = calculate_price(call, S, K, T, r, sigma, q);
            double vega = calculate_vega(S, K, T, r, sigma, q) * 100.0;
            double diff = price - market_price;

            if (std::abs(diff) < tol) {
                return sigma;
            }

            if (vega < 1e-10) {
                return std::numeric_limits<double>::quiet_NaN();
            }

            sigma -= diff / vega;
            if (sigma <= 0.0) {
                sigma = 0.01;
            }
        }

        return std::numeric_limits<double>::quiet_NaN();
    }
}