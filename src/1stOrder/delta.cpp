#include "Greeks.h"
#include "math/cdf.h"
#include "math/d1.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_delta(bool call, double S, double K, double T, double r, double sigma, double q) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        return call ? exp_dividend(q, T) * normal_cdf(d1) : exp_dividend(q, T) * (normal_cdf(d1) - 1.0);
    }
}