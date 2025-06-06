#include "Greeks.h"
#include "math/cdf.h"
#include "math/d1.h"
#include "math/d2.h"
#include "math/maths.h"
#include "math/common.h"

namespace GreeksCalculator {
    double calculate_price(bool call, double S, double K, double T, double r, double sigma, double q) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        if (call) {
            return S * exp_dividend(q, T) * normal_cdf(d1) - K * safe_exp(-r * T) * normal_cdf(d2);
        } else {
            return K * safe_exp(-r * T) * normal_cdf(-d2) - S * exp_dividend(q, T) * normal_cdf(-d1);
        }
    }
}