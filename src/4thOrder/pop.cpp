#include "Greeks.h"
#include "math/d1.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_pop(double S, double K, double T, double r, double sigma, double q) {
        double snap = calculate_snap(S, K, T, r, sigma, q);
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double term = d1 * d1 * d1 - 6.0 * d1 * d1 / sigma_sqrt_time(sigma, T) - 3.0 * d1 - 3.0 / sigma_sqrt_time(sigma, T);
        return snap * term / S;
    }
}