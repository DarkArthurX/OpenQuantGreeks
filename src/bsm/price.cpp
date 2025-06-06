#include "bsm/price.h"
#include "bsm/validation.h"
#include "Greeks.h"

namespace GreeksCalculator {
    double bsm_price(bool call, double S, double K, double T, double r, double sigma, double q) {
        validate_inputs(S, K, T, r, sigma, q);
        return calculate_price(call, S, K, T, r, sigma, q);
    }
}