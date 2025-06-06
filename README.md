# Options Greeks Library

A comprehensive C++ library for calculating options Greeks using the Black-Scholes-Merton model. This library is designed for quantitative traders, risk managers, and anyone working with options pricing and risk analysis.

## What Are "Greeks"?

Greeks are mathematical measures that describe how an option's price changes when different market conditions change. Think of them as "sensitivity measures" - they tell you how much your option's value will move when the underlying stock price, volatility, time, or interest rates change.

Just like a car's speedometer tells you how fast you're going, Greeks tell you how your options portfolio will react to market movements.

## Why Use This Library?

### Configurable Scaling for Different Trading Styles

**The Problem**: Traditional options libraries assume you always want daily time decay and 1% sensitivity measures. But if you're:
- **Intraday trading**: Daily theta scaling is useless - you need annual or hourly
- **Institutional trading**: You might want 1 basis point (0.01%) sensitivity instead of 1%
- **Risk management**: You need unscaled values for your own calculations

**The Solution**: User-configurable scaling parameters.

```cpp
// For intraday trading - no time scaling
Greeks intraday = calculate_all(call, S, K, T, r, vol, q, ScalingParams::intraday());

// For institutional - 1 basis point sensitivity  
ScalingParams institutional;
institutional.rho_scale = 10000.0;  // 1bp instead of 1%
Greeks precise = calculate_all(call, S, K, T, r, vol, q, institutional);

// Traditional daily scaling
Greeks standard = calculate_all(call, S, K, T, r, vol, q, ScalingParams::standard());
```

### Comprehensive Greek Coverage

This library calculates Greeks up to 6th order derivatives:
- **1st Order**: Basic sensitivities (Delta, Vega, Theta, Rho, Epsilon)
- **2nd Order**: Rate of change of 1st order Greeks (Gamma, Vanna, Charm, etc.)
- **3rd-6th Order**: Higher-order sensitivities for advanced risk management

### Production-Ready with Safeguards

- **Numerical stability**: Safe division and logarithm functions prevent crashes
- **Boundary conditions**: Higher-order Greeks automatically return NaN for extreme parameters
- **Comprehensive testing**: Full test suite ensures mathematical accuracy

## Quick Start

### Basic Usage

```cpp
#include "Greeks.h"
using namespace GreeksCalculator;

// Standard European call option
double S = 100.0;    // Stock price
double K = 105.0;    // Strike price  
double T = 0.25;     // Time to expiration (0.25 = 3 months)
double r = 0.05;     // Risk-free rate (5%)
double vol = 0.20;   // Volatility (20%)
double q = 0.02;     // Dividend yield (2%)

// Calculate all Greeks with standard scaling
Greeks g = calculate_all(true, S, K, T, r, vol, q);

printf("Delta: %.4f (per $1 stock move)\n", g.delta);
printf("Vega: %.4f (per 1%% vol change)\n", g.vega);  
printf("Theta: %.4f (per day)\n", g.theta);
```

### Scaling Examples

```cpp
// Intraday trading - get theta per year, not per day
Greeks intraday = calculate_all(true, S, K, T, r, vol, q, ScalingParams::intraday());
printf("Annual theta: %.4f\n", intraday.theta);  // No daily scaling

// High-frequency trading - get vega per 0.1% vol change
ScalingParams hft;
hft.vega_scale = 1000.0;  // 0.1% instead of 1%
Greeks precise = calculate_all(true, S, K, T, r, vol, q, hft);
printf("Vega per 10bp vol: %.4f\n", precise.vega);

// Risk management - unscaled values for your own calculations
Greeks raw = calculate_all(true, S, K, T, r, vol, q, ScalingParams::no_scaling());
printf("Raw vega: %.6f\n", raw.vega);  // Unscaled mathematical value
```

## Greek Definitions by Order

### 1st Order Greeks (Primary Sensitivities)
- **Delta (Δ)**: Price sensitivity to stock price changes
- **Vega (ν)**: Price sensitivity to volatility changes  
- **Theta (Θ)**: Price sensitivity to time decay
- **Rho (ρ)**: Price sensitivity to interest rate changes
- **Epsilon (ε)**: Price sensitivity to dividend yield changes

### 2nd Order Greeks (Rate of Change)
- **Gamma (Γ)**: Rate of change of Delta
- **Vanna**: Rate of change of Delta with respect to volatility
- **Charm**: Rate of change of Delta with respect to time
- **Volga**: Rate of change of Vega with respect to volatility

### Higher Order Greeks (3rd-6th)
These measure how the 2nd order Greeks change, providing insights into portfolio convexity and stability under extreme market conditions.

⚠️ **Production Warning**: Higher-order Greeks (3rd order and above) should be thoroughly tested before use in production systems. Their practical utility varies significantly based on market conditions and trading strategies.

## Building the Library

```bash
mkdir build && cd build
cmake ..
make
```

### Running Tests

```bash
./greeks_tests
```

The test suite verifies mathematical accuracy against known benchmark values and tests the scaling functionality.

## Advanced Features

### Numerical Stability
The library includes robust handling of edge cases:
- Safe logarithms for extreme stock prices
- Safe division to prevent overflow/underflow
- Automatic NaN return for invalid parameter combinations

### Boundary Conditions
Higher-order Greeks automatically return NaN when:
- Time to expiration is too short
- Volatility is too low
- Other parameters are outside stable calculation ranges

This prevents misleading results from numerically unstable calculations.

## Architecture

```
src/
├── 1stOrder/          # Primary Greeks (Delta, Vega, Theta, Rho, Epsilon)
├── 2ndOrder/          # Second derivatives (Gamma, Vanna, Charm, etc.)
├── 3rdOrder/          # Third derivatives (Speed, Zomma, Color, etc.)
├── 4thOrder/          # Fourth derivatives  
├── 5thOrder/          # Fifth derivatives
├── 6thOrder/          # Sixth derivatives
├── math/              # Mathematical foundations (d1, d2, CDF, PDF)
├── bsm/               # Black-Scholes-Merton pricing functions
└── Greeks.h           # Main interface and ScalingParams
```

Each directory contains a detailed README explaining the specific Greeks calculated there.

## Branches

I maintain a few branches, if you have an idea, try to follow this scheme.

- Main - this will be the portable stable branch, "generically" written.
- Vectorized - Main + Vector Extensions
- Vectorized_* - The vectorized extensions + other optimizations.
- 
## Contributing

1. Ensure your changes pass all existing tests
2. Add tests for new functionality
3. Update relevant README files
4. Follow the existing code style and structure


The library is designed to be mathematically rigorous while remaining accessible to practitioners across different trading styles and timeframes.
