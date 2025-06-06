#include "Greeks.h"
#include "math/d1.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_pounce(double S, double K, double T, double r, double sigma, double q) {
        double jounce = calculate_jounce(S, K, T, r, sigma, q);
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double term = d1 * d1 * d1 * d1 - 9.0 * d1 * d1 * d1 / sigma_sqrt_time(sigma, T) + 31.0 * d1 * d1 / (sigma * sigma * T) - 27.0 * d1 / (sigma * sigma * sigma * pow(sqrt_time(T), 3)) - 9.0;
        return jounce * term / (S * S);
    }
}