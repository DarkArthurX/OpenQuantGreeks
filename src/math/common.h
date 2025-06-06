#pragma once
#include "Greeks.h"

namespace GreeksCalculator {
    double exp_dividend(double q, double T);
    double sqrt_time(double T);
    double sigma_sqrt_time(double sigma, double T);
    
    // Legacy scaling functions - deprecated
    double scale_percent(double value);
    double scale_daily(double value);
    
    // New configurable scaling functions
    double scale_vega(double value, const ScalingParams& scaling);
    double scale_rho(double value, const ScalingParams& scaling);
    double scale_epsilon(double value, const ScalingParams& scaling);
    double scale_theta(double value, const ScalingParams& scaling);
    double scale_charm(double value, const ScalingParams& scaling);
    double scale_color(double value, const ScalingParams& scaling);
}