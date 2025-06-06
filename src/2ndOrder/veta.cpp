#include "Greeks.h"
#include "math/pdf.h"
#include "math/d1.h"
#include "math/d2.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_veta(double S, double K, double T, double r, double sigma, double q, const ScalingParams& scaling) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        double term = -S * exp_dividend(q, T) * normal_pdf(d1) * sqrt_time(T) * (q + safe_divide((r - q - d1 * sigma / (2.0 * T)) * d2, sigma));
        return scale_vega(scale_charm(term, scaling), scaling);
    }
}