#include "Greeks.h"
#include "math/cdf.h"
#include "math/d1.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_epsilon(bool call, double S, double K, double T, double r, double sigma, double q, const ScalingParams& scaling) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        if (call) {
            return scale_epsilon(-S * T * exp_dividend(q, T) * normal_cdf(d1), scaling);
        } else {
            return scale_epsilon(S * T * exp_dividend(q, T) * normal_cdf(-d1), scaling);
        }
    }
}