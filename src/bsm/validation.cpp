#include "bsm/validation.h"
#include <stdexcept>

namespace GreeksCalculator {
    void validate_inputs(double S, double K, double T, double r, double sigma, double q) {
        if (S <= 0.0 || K <= 0.0 || T <= 0.0 || sigma <= 0.0) {
            throw std::invalid_argument("Invalid Black-Scholes-Merton parameters: S, K, T, and sigma must be positive.");
        }
    }
}