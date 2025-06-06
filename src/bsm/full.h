#pragma once

#include "Greeks.h"

namespace GreeksCalculator {
    Greeks bsm_full(bool call, double S, double K, double T, double r, double sigma, double q = 0.0);
}