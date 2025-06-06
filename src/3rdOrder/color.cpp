#include "Greeks.h"
#include "math/pdf.h"
#include "math/d1.h"
#include "math/d2.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_color(double S, double K, double T, double r, double sigma, double q) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        double term = normal_pdf(d1) * exp_dividend(q, T) * (safe_divide(d1, sigma_sqrt_time(sigma, T)) + 1.0) * (2.0 * (r - q) * T - d2 * sigma_sqrt_time(sigma, T));
        return scale_daily(-term / (2.0 * S * T * sigma_sqrt_time(sigma, T)));
    }
}