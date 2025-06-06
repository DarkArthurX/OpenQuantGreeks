#include "bsm/full.h"
#include "bsm/validation.h"
#include "Greeks.h"

namespace GreeksCalculator {
    Greeks bsm_full(bool call, double S, double K, double T, double r, double sigma, double q) {
        validate_inputs(S, K, T, r, sigma, q);
        return calculate_all(call, S, K, T, r, sigma, q);
    }
}