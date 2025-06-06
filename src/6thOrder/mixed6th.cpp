#include "Greeks.h"
#include "math/pdf.h"
#include "math/d1.h"
#include "math/d2.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_mixed6th(double S, double K, double T, double r, double sigma, double q) {
        if (T < 5.0 / 365.0 || sigma < 0.15) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        double sqrtT = sqrt_time(T);
        double sigma_sqrtT = sigma_sqrt_time(sigma, T);

        double gamma = safe_divide(normal_pdf(d1) * exp_dividend(q, T), S * sigma_sqrtT);

        double term1 = d1 * d1 * d1 - 3.0 * d1 * d1 / sigma_sqrtT - 3.0 * d1;
        double term2 = d1 * d2 * (1.0 - d1 * d2) + d1 * d1 + d2 * d2;
        double term3 = safe_divide(r - q - d1 * sigma / (2.0 * T), sigma);

        double result = gamma * term1 * term2 * term3 / (S * S * sigma);
        return scale_percent(scale_daily(result));
    }
}