#include "Greeks.h"
#include "math/pdf.h"
#include "math/d1.h"
#include "math/d2.h"
#include "math/maths.h"
#include "math/common.h"

namespace GreeksCalculator {
    double calculate_volga(double S, double K, double T, double r, double sigma, double q, const ScalingParams& scaling) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        return scale_vega(S * exp_dividend(q, T) * normal_pdf(d1) * sqrt_time(T) * d1 * d2 / sigma, scaling);
    }
}