#include "math/pdf.h"
#include <cmath>

namespace GreeksCalculator {
    double normal_pdf(double x) {
        return exp(-0.5 * x * x) / sqrt(2.0 * M_PI);
    }
}
