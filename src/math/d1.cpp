#include "math/d1.h"
#include "math/maths.h"
#include "math/common.h"
#include <cmath>

namespace GreeksCalculator {
    double calculate_d1(double S, double K, double T, double r, double sigma, double q) {
        double log_term = safe_log(S / K);
        if (!is_valid(log_term)) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double numerator = log_term + (r - q + 0.5 * sigma * sigma) * T;
        double denominator = sigma * sqrt_time(T);
        return safe_divide(numerator, denominator);
    }
}