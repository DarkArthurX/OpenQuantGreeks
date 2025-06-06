#pragma once

namespace GreeksCalculator {
    double bsm_price(bool call, double S, double K, double T, double r, double sigma, double q = 0.0);
}