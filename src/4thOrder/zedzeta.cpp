#include "Greeks.h"
#include "math/d1.h"
#include "math/d2.h"
#include "math/pdf.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_zed_zeta(double S, double K, double T, double r, double sigma, double q) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        // Use unscaled vega calculation to avoid triple scaling
        double vega_unscaled = S * exp_dividend(q, T) * normal_pdf(d1) * sqrt_time(T);
        return scale_percent(vega_unscaled * (d1 * d2 * (1.0 - d1 * d2) + d1 * d1 + d2 * d2) / (sigma * sigma));
    }
}