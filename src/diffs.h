#pragma once
#include <functional>

namespace GreeksCalculator {
    double central_difference(std::function<double(double)> f, double x, double h = 1e-4);
    double second_central_difference(std::function<double(double)> f, double x, double h = 1e-4);
    double fifth_order_difference(std::function<double(double)> f, double x, double h = 1e-4);
    double mixed_partial(std::function<double(double, double)> f, double x, double y, double h = 1e-4, double k = 1e-4);
    double adaptive_step(double value, double min_h = 1e-6, double scale = 0.01);
    double numerical_delta(bool call, double S, double K, double T, double r, double sigma, double q = 0.0);
}