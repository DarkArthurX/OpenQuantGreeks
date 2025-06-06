#include "math/d2.h"
#include "math/d1.h"
#include "math/maths.h"
#include "math/common.h"
#include <cmath>

namespace GreeksCalculator {
    double calculate_d2(double S, double K, double T, double r, double sigma, double q) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        if (!is_valid(d1)) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return d1 - sigma * sqrt_time(T);
    }
}