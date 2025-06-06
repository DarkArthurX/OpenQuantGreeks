#include "Greeks.h"
#include "math/cdf.h"
#include "math/d2.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_rho(bool call, double S, double K, double T, double r, double sigma, double q, const ScalingParams& scaling) {
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        if (call) {
            return scale_rho(K * T * safe_exp(-r * T) * normal_cdf(d2), scaling);
        } else {
            return scale_rho(-K * T * safe_exp(-r * T) * normal_cdf(-d2), scaling);
        }
    }
}