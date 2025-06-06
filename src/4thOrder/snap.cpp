#include "Greeks.h"
#include "math/d1.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_snap(double S, double K, double T, double r, double sigma, double q) {
        double gamma = calculate_gamma(S, K, T, r, sigma, q);
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double term = d1 * d1 - 3.0 * safe_divide(d1, sigma_sqrt_time(sigma, T)) - 1.0;
        return gamma * term / (S * S);
    }
}