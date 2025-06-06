#include "Greeks.h"
#include "math/pdf.h"
#include "math/cdf.h"
#include "math/d1.h"
#include "math/d2.h"
#include "math/common.h"
#include "math/maths.h"


namespace GreeksCalculator {
    double calculate_theta(bool call, double S, double K, double T, double r, double sigma, double q, const ScalingParams& scaling) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        double term1 = -S * exp_dividend(q, T) * normal_pdf(d1) * sigma / (2.0 * sqrt_time(T));
        double term2 = q * S * exp_dividend(q, T) * normal_cdf(d1);
        double term3 = -r * K * safe_exp(-r * T) * normal_cdf(d2);
        if (!call) {
            term2 = -q * S * exp_dividend(q, T) * normal_cdf(-d1);
            term3 = r * K * safe_exp(-r * T) * normal_cdf(-d2);
        }
        return scale_theta(term1 - term2 + term3, scaling);
    }
}