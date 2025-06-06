#pragma once
#include <cmath>
#include <limits>
#include <string>
#include <functional>

struct ScalingParams {
    double vega_scale = 100.0;        // Default: per 1% vol change (divide by 100)
    double rho_scale = 100.0;         // Default: per 1% rate change (divide by 100) 
    double epsilon_scale = 100.0;     // Default: per 1% dividend yield change (divide by 100)
    double theta_scale = 365.0;       // Default: annual to daily (divide by 365)
    double charm_scale = 365.0;       // Default: annual to daily (divide by 365)
    double color_scale = 365.0;       // Default: annual to daily (divide by 365)
    
    // Factory methods for common use cases
    static ScalingParams no_scaling() {
        return {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    }
    
    static ScalingParams intraday() {
        return {100.0, 100.0, 100.0, 1.0, 1.0, 1.0}; // No time scaling for intraday
    }
    
    static ScalingParams weekly() {
        return {100.0, 100.0, 100.0, 52.0, 52.0, 52.0}; // Weekly time scaling
    }
    
    static ScalingParams standard() {
        return {100.0, 100.0, 100.0, 365.0, 365.0, 365.0}; // Default scaling
    }
};

struct Greeks {
    double price = std::numeric_limits<double>::quiet_NaN();
    double delta = std::numeric_limits<double>::quiet_NaN();
    double vega = std::numeric_limits<double>::quiet_NaN();
    double theta = std::numeric_limits<double>::quiet_NaN();
    double rho = std::numeric_limits<double>::quiet_NaN();
    double lambda = std::numeric_limits<double>::quiet_NaN();
    double epsilon = std::numeric_limits<double>::quiet_NaN();

    double gamma = std::numeric_limits<double>::quiet_NaN();
    double vanna = std::numeric_limits<double>::quiet_NaN();
    double charm = std::numeric_limits<double>::quiet_NaN();
    double volga = std::numeric_limits<double>::quiet_NaN();
    double veta = std::numeric_limits<double>::quiet_NaN();
    double vera = std::numeric_limits<double>::quiet_NaN();
    double dual_rho = std::numeric_limits<double>::quiet_NaN();

    double speed = std::numeric_limits<double>::quiet_NaN();
    double zomma = std::numeric_limits<double>::quiet_NaN();
    double color = std::numeric_limits<double>::quiet_NaN();
    double ultima = std::numeric_limits<double>::quiet_NaN();
    double dvanna_dvol = std::numeric_limits<double>::quiet_NaN();

    double snap = std::numeric_limits<double>::quiet_NaN();
    double zed_zeta = std::numeric_limits<double>::quiet_NaN();
    double crackle = std::numeric_limits<double>::quiet_NaN();
    double pop = std::numeric_limits<double>::quiet_NaN();

    double jounce = std::numeric_limits<double>::quiet_NaN();
    double quintema = std::numeric_limits<double>::quiet_NaN();
    double mixed5th = std::numeric_limits<double>::quiet_NaN();

    double pounce = std::numeric_limits<double>::quiet_NaN();
    double hexema = std::numeric_limits<double>::quiet_NaN();
    double mixed6th = std::numeric_limits<double>::quiet_NaN();
};

namespace GreeksCalculator {
    
    double calculate_price(bool call, double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_delta(bool call, double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_vega(double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());
    double calculate_theta(bool call, double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());
    double calculate_rho(bool call, double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());
    double calculate_lambda(bool call, double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_epsilon(bool call, double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());

    double calculate_gamma(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_vanna(double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());
    double calculate_charm(bool call, double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());
    double calculate_volga(double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());
    double calculate_veta(double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());
    double calculate_vera(double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());
    double calculate_dual_rho(double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());

    double calculate_speed(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_zomma(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_color(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_ultima(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_dvanna_dvol(double S, double K, double T, double r, double sigma, double q = 0.0);

    double calculate_snap(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_zed_zeta(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_crackle(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_pop(double S, double K, double T, double r, double sigma, double q = 0.0);

    double calculate_jounce(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_quintema(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_mixed5th(double S, double K, double T, double r, double sigma, double q = 0.0);

    double calculate_pounce(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_hexema(double S, double K, double T, double r, double sigma, double q = 0.0);
    double calculate_mixed6th(double S, double K, double T, double r, double sigma, double q = 0.0);

    Greeks calculate_all(bool call, double S, double K, double T, double r, double sigma, double q = 0.0, const ScalingParams& scaling = ScalingParams::standard());
}