#include "Greeks.h"
#include "math/pdf.h"
#include "math/d1.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_gamma(double S, double K, double T, double r, double sigma, double q) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        return safe_divide(normal_pdf(d1) * exp_dividend(q, T), S * sigma_sqrt_time(sigma, T));
    }
}