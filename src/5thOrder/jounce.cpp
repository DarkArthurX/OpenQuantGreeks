#include "Greeks.h"
#include "math/d1.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_jounce(double S, double K, double T, double r, double sigma, double q) {
        double snap = calculate_snap(S, K, T, r, sigma, q);
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double term = d1 * d1 * d1 - 5.0 * d1 * d1 / sigma_sqrt_time(sigma, T) + 5.0 * d1 / (sigma * sigma * T) + 3.0;
        return snap * term / S;
    }
}