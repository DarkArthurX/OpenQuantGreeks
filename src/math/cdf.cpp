#include "math/cdf.h"
#include <cmath>

namespace GreeksCalculator {
    double normal_cdf(double x) {
        return 0.5 * (1.0 + erf(x / sqrt(2.0)));
    }
}