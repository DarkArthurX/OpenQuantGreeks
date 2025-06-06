#include "math/maths.h"
#include <cmath>
#include <stdexcept>

namespace GreeksCalculator {
    double safe_divide(double numerator, double denominator, double epsilon) {
        if (std::abs(denominator) < epsilon) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return numerator / denominator;
    }

    double safe_log(double x) {
        if (x <= 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return std::log(x);
    }

    double clamp(double x, double min_val, double max_val) {
        return std::max(min_val, std::min(max_val, x));
    }

    double safe_exp(double x) {
        if (x > 709.0) {
            return std::numeric_limits<double>::max();
        }
        if (x < -709.0) {
            return 0.0;
        }
        return std::exp(x);
    }

    bool is_valid(double x) {
        return std::isfinite(x);
    }

    double lerp(double a, double b, double t) {
        return a + t * (b - a);
    }
}