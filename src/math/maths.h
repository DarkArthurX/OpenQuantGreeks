#pragma once

namespace GreeksCalculator {
    double safe_divide(double numerator, double denominator, double epsilon = 1e-10);
    double safe_log(double x);
    double clamp(double x, double min_val, double max_val);
    double safe_exp(double x);
    bool is_valid(double x);
    double lerp(double a, double b, double t);
}