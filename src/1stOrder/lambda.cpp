#include "Greeks.h"
#include "math/maths.h"

namespace GreeksCalculator {
    double calculate_lambda(bool call, double S, double K, double T, double r, double sigma, double q) {
        double delta = calculate_delta(call, S, K, T, r, sigma, q);
        double price = calculate_price(call, S, K, T, r, sigma, q);
        return safe_divide(delta * S, price);
    }
}