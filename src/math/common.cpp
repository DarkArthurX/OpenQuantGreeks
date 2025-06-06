#include "math/common.h"
#include "math/maths.h"
#include <cmath>

namespace GreeksCalculator {
    double exp_dividend(double q, double T) {
        return safe_exp(-q * T);
    }

    double sqrt_time(double T) {
        if (T <= 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return sqrt(T);
    }

    double sigma_sqrt_time(double sigma, double T) {
        if (sigma <= 0.0 || T <= 0.0) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return sigma * sqrt_time(T);
    }

    double scale_percent(double value) {
        return safe_divide(value, 100.0);
    }

    double scale_daily(double value) {
        return safe_divide(value, 365.0);
    }

    double scale_vega(double value, const ScalingParams& scaling) {
        return safe_divide(value, scaling.vega_scale);
    }

    double scale_rho(double value, const ScalingParams& scaling) {
        return safe_divide(value, scaling.rho_scale);
    }

    double scale_epsilon(double value, const ScalingParams& scaling) {
        return safe_divide(value, scaling.epsilon_scale);
    }

    double scale_theta(double value, const ScalingParams& scaling) {
        return safe_divide(value, scaling.theta_scale);
    }

    double scale_charm(double value, const ScalingParams& scaling) {
        return safe_divide(value, scaling.charm_scale);
    }

    double scale_color(double value, const ScalingParams& scaling) {
        return safe_divide(value, scaling.color_scale);
    }
}