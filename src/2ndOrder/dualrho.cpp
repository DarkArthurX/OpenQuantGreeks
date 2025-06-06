#include "Greeks.h"
#include "math/pdf.h"
#include "math/d2.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_dual_rho(double S, double K, double T, double r, double sigma, double q, const ScalingParams& scaling) {
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        return scale_rho(-T * T * K * safe_exp(-r * T) * normal_pdf(d2) * sigma / (2.0 * sqrt_time(T)), scaling);
    }
}