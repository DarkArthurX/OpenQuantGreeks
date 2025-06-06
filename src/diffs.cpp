#include "diffs.h"
#include "Greeks.h"
#include <cmath>

namespace GreeksCalculator {
    double central_difference(std::function<double(double)> f, double x, double h) {
        if (h <= 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return (f(x + h) - f(x - h)) / (2.0 * h);
    }

    double second_central_difference(std::function<double(double)> f, double x, double h) {
        if (h <= 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return (f(x + h) - 2.0 * f(x) + f(x - h)) / (h * h);
    }

    double fifth_order_difference(std::function<double(double)> f, double x, double h) {
        if (h <= 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return (-f(x + 2.0 * h) + 8.0 * f(x + h) - 8.0 * f(x - h) + f(x - 2.0 * h)) / (12.0 * h);
    }

    double mixed_partial(std::function<double(double, double)> f, double x, double y, double h, double k) {
        if (h <= 0.0 || k <= 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return (f(x + h, y + k) - f(x + h, y - k) - f(x - h, y + k) + f(x - h, y - k)) / (4.0 * h * k);
    }

    double adaptive_step(double value, double min_h, double scale) {
        return std::max(min_h, std::abs(value) * scale);
    }

    double numerical_delta(bool call, double S, double K, double T, double r, double sigma, double q) {
        auto price_func = [=](double s) { return calculate_price(call, s, K, T, r, sigma, q); };
        double h = adaptive_step(S);
        return central_difference(price_func, S, h);
    }
}