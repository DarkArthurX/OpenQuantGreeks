#include "Greeks.h"
#include "math/pdf.h"
#include "math/d1.h"
#include "math/d2.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_vera(double S, double K, double T, double r, double sigma, double q, const ScalingParams& scaling) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        return scale_rho(-K * T * safe_exp(-r * T) * normal_pdf(d2) * sqrt_time(T) * d1, scaling);
    }
}