#include "Greeks.h"

namespace GreeksCalculator {
    Greeks calculate_all(bool call, double S, double K, double T, double r, double sigma, double q, const ScalingParams& scaling) {
        Greeks g;

		g.price = calculate_price(call, S, K, T, r, sigma, q);
		g.delta = calculate_delta(call, S, K, T, r, sigma, q);
		g.vega = calculate_vega(S, K, T, r, sigma, q, scaling);
		g.theta = calculate_theta(call, S, K, T, r, sigma, q, scaling);
		g.rho = calculate_rho(call, S, K, T, r, sigma, q, scaling);
		g.lambda = calculate_lambda(call, S, K, T, r, sigma, q);
		g.epsilon = calculate_epsilon(call, S, K, T, r, sigma, q, scaling);

		g.gamma = calculate_gamma(S, K, T, r, sigma, q);
		g.vanna = calculate_vanna(S, K, T, r, sigma, q, scaling);
		g.charm = calculate_charm(call, S, K, T, r, sigma, q, scaling);
		g.volga = calculate_volga(S, K, T, r, sigma, q, scaling);
		g.veta = calculate_veta(S, K, T, r, sigma, q, scaling);
		g.vera = calculate_vera(S, K, T, r, sigma, q, scaling);
		g.dual_rho = calculate_dual_rho(S, K, T, r, sigma, q, scaling);

		g.speed = calculate_speed(S, K, T, r, sigma, q);
		g.zomma = calculate_zomma(S, K, T, r, sigma, q);
		g.color = calculate_color(S, K, T, r, sigma, q);
		g.ultima = calculate_ultima(S, K, T, r, sigma, q);
		g.dvanna_dvol = calculate_dvanna_dvol(S, K, T, r, sigma, q);

		if (T > 1.0 / 365.0 && sigma > 0.05) {
		g.snap = calculate_snap(S, K, T, r, sigma, q);
		g.zed_zeta = calculate_zed_zeta(S, K, T, r, sigma, q);
		g.crackle = calculate_crackle(S, K, T, r, sigma, q);
		g.pop = calculate_pop(S, K, T, r, sigma, q);
        }

		if (T > 2.0 / 365.0 && sigma > 0.10) {
		g.jounce = calculate_jounce(S, K, T, r, sigma, q);
		g.quintema = calculate_quintema(S, K, T, r, sigma, q);
		g.mixed5th = calculate_mixed5th(S, K, T, r, sigma, q);
        }

		if (T > 5.0 / 365.0 && sigma > 0.15) {
		g.pounce = calculate_pounce(S, K, T, r, sigma, q);
		g.hexema = calculate_hexema(S, K, T, r, sigma, q);
		g.mixed6th = calculate_mixed6th(S, K, T, r, sigma, q);
        }

        return g;
    }
}