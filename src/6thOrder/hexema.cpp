#include "Greeks.h"
#include "math/d1.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_hexema(double S, double K, double T, double r, double sigma, double q) {
        double pounce = calculate_pounce(S, K, T, r, sigma, q);
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double term = d1 * d1 * d1 * d1 * d1 - 11.0 * d1 * d1 * d1 * d1 / sigma_sqrt_time(sigma, T) + 49.0 * d1 * d1 * d1 / (sigma * sigma * T) - 69.0 * d1 * d1 / (sigma * sigma * sigma * pow(sqrt_time(T), 3)) + 39.0 * d1 / (sigma * sigma * sigma * sigma * pow(sqrt_time(T), 4)) + 10.0;
        return pounce * term / S;
    }
}