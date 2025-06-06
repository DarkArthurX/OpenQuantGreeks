#include "Greeks.h"
#include "math/pdf.h"
#include "math/d1.h"
#include "math/d2.h"
#include "math/common.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_dvanna_dvol(double S, double K, double T, double r, double sigma, double q) {
        double d1 = calculate_d1(S, K, T, r, sigma, q);
        double d2 = calculate_d2(S, K, T, r, sigma, q);
        return scale_percent(exp_dividend(q, T) * normal_pdf(d1) * (1.0 - d1 * d2) / (sigma * sigma));
    }
}