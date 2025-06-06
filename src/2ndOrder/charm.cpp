#include "Greeks.h"
#include "math/pdf.h"
#include "math/cdf.h"
#include "math/d1.h"
#include "math/d2.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_charm(bool call, double S, double K, double T, double r, double sigma, double q, const ScalingParams& scaling) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        double term1 = q * exp_dividend(q, T) * normal_cdf(d1);
        double term2 = exp_dividend(q, T) * normal_pdf(d1) * safe_divide((2.0 * (r - q) * T - d2 * sigma_sqrt_time(sigma, T)), (2.0 * T * sigma_sqrt_time(sigma, T)));
        if (!call) {
            term1 = -q * exp_dividend(q, T) * normal_cdf(-d1);
            term2 = -exp_dividend(q, T) * normal_pdf(d1) * safe_divide((2.0 * (r - q) * T - d2 * sigma_sqrt_time(sigma, T)), (2.0 * T * sigma_sqrt_time(sigma, T)));
        }
        return scale_charm(term1 - term2, scaling);
    }
}