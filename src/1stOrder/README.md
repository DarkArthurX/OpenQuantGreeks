# First Order Greeks - Primary Sensitivities

First order Greeks are the fundamental risk measures every options trader needs to understand. They tell you how your option's price changes when market conditions shift. These are the "bread and butter" Greeks used in daily trading and risk management.

## The Greeks Explained

### Delta (Δ) - Stock Price Sensitivity
**What it measures**: How much the option price changes when the stock price moves $1.

**Think of it as**: The "speed" of your option relative to the stock.

**Practical examples**:
- Delta = 0.50 means if the stock goes up $1, your option gains ~$0.50
- Call options: Delta ranges from 0 to 1.0
- Put options: Delta ranges from -1.0 to 0

**Trading insights**:
- High Delta (near 1.0): Option moves almost dollar-for-dollar with stock
- Low Delta (near 0): Option barely moves when stock moves
- At-the-money options typically have Delta around 0.50

```cpp
double delta = calculate_delta(true, 100, 100, 0.25, 0.05, 0.20, 0.02);
printf("For every $1 stock move, option moves $%.2f\n", delta);
```

### Vega (ν) - Volatility Sensitivity  
**What it measures**: How much the option price changes when volatility changes by 1%.

**Think of it as**: How much your option benefits from increased uncertainty.

**Practical examples**:
- Vega = 0.25 means if volatility increases from 20% to 21%, option gains $0.25
- All options have positive Vega (more volatility = higher prices)
- Long options want high volatility, short options want low volatility

**Trading insights**:
- High Vega: Option very sensitive to volatility changes (good for volatility plays)
- Low Vega: Option price stable regardless of volatility changes
- Vega highest for at-the-money options with medium time to expiration

```cpp
// Standard scaling: per 1% volatility change
double vega = calculate_vega(100, 100, 0.25, 0.05, 0.20, 0.02);

// Custom scaling: per 0.1% (10 basis points) volatility change  
ScalingParams precise;
precise.vega_scale = 1000.0;
double vega_10bp = calculate_vega(100, 100, 0.25, 0.05, 0.20, 0.02, precise);
```

### Theta (Θ) - Time Decay
**What it measures**: How much the option loses value each day due to time passing.

**Think of it as**: The "rent" you pay for holding the option.

**Practical examples**:
- Theta = -0.05 means your option loses $0.05 in value each day
- All options have negative Theta (time decay hurts option buyers)
- Theta accelerates as expiration approaches

**Trading insights**:
- High negative Theta: Option losing value quickly (bad for option buyers)
- Theta highest for at-the-money options near expiration
- Time decay is non-linear - accelerates in final weeks

```cpp
// Standard: daily time decay
double theta_daily = calculate_theta(true, 100, 100, 0.25, 0.05, 0.20, 0.02);

// Intraday trading: annual time decay (no daily scaling)
double theta_annual = calculate_theta(true, 100, 100, 0.25, 0.05, 0.20, 0.02, 
                                    ScalingParams::intraday());
printf("Daily decay: $%.4f, Annual decay: $%.2f\n", theta_daily, theta_annual);
```

### Rho (ρ) - Interest Rate Sensitivity
**What it measures**: How much the option price changes when interest rates change by 1%.

**Think of it as**: How monetary policy affects your options.

**Practical examples**:
- Rho = 0.15 means if interest rates rise from 5% to 6%, option gains $0.15
- Call options have positive Rho (higher rates = higher call prices)
- Put options have negative Rho (higher rates = lower put prices)

**Trading insights**:
- Rho matters more for longer-term options
- Usually the least important Greek for short-term trading
- Can be significant during Fed meetings or rate changes

```cpp
// Standard: per 1% interest rate change
double rho = calculate_rho(true, 100, 100, 0.25, 0.05, 0.20, 0.02);

// Institutional: per 1 basis point (0.01%) change
ScalingParams institutional;
institutional.rho_scale = 10000.0;
double rho_1bp = calculate_rho(true, 100, 100, 0.25, 0.05, 0.20, 0.02, institutional);
```

### Epsilon (ε) - Dividend Sensitivity
**What it measures**: How much the option price changes when dividend yield changes by 1%.

**Think of it as**: How dividend announcements affect your options.

**Practical examples**:
- Epsilon = -0.20 means if dividends increase from 2% to 3%, option loses $0.20
- Call options have negative Epsilon (higher dividends = lower call prices)
- Put options have positive Epsilon (higher dividends = higher put prices)

**Trading insights**:
- Most important around ex-dividend dates
- Dividend captures and special dividends can cause significant moves
- Often overlooked but can be crucial for dividend-paying stocks

```cpp
double epsilon = calculate_epsilon(true, 100, 100, 0.25, 0.05, 0.20, 0.02);
printf("Dividend sensitivity: $%.4f per 1%% yield change\n", epsilon);
```

### Lambda (λ) - Leverage Factor
**What it measures**: The option's effective leverage compared to owning the stock.

**Think of it as**: How much "bang for your buck" the option provides.

**Practical examples**:
- Lambda = 5.0 means the option provides 5x the percentage return of the stock
- Higher Lambda = more leverage = more risk and reward
- Calculated as (Delta × Stock Price) / Option Price

**Trading insights**:
- Cheap out-of-the-money options often have very high Lambda
- High Lambda options are very risky but offer high potential returns
- Lambda changes as stock price and option price change

```cpp
double lambda = calculate_lambda(true, 100, 100, 0.25, 0.05, 0.20, 0.02);
printf("Option provides %.1fx leverage vs. stock\n", lambda);
```

## Scaling Configurations

All first order Greeks (except Delta and Lambda) support configurable scaling:

```cpp
// Standard daily and 1% scaling
ScalingParams standard = ScalingParams::standard();
// theta_scale = 365, vega_scale = 100, rho_scale = 100, epsilon_scale = 100

// Intraday trading
ScalingParams intraday = ScalingParams::intraday(); 
// theta_scale = 1 (no daily scaling), others = 100

// No scaling (raw mathematical values)
ScalingParams raw = ScalingParams::no_scaling();
// All scales = 1

// Custom scaling
ScalingParams custom;
custom.theta_scale = 252.0;    // Business days per year
custom.vega_scale = 1000.0;    // Per 0.1% vol change
custom.rho_scale = 10000.0;    // Per 1 basis point
custom.epsilon_scale = 100.0;  // Per 1% dividend change
```

## Usage Patterns

### Risk Management
```cpp
Greeks g = calculate_all(true, S, K, T, r, vol, q);
double portfolio_delta = position_size * g.delta;
double daily_theta_decay = position_size * g.theta;
printf("Portfolio delta exposure: %.0f\n", portfolio_delta);
printf("Daily time decay: $%.2f\n", daily_theta_decay);
```

### Volatility Trading
```cpp
Greeks g = calculate_all(true, S, K, T, r, vol, q);
double vol_exposure = position_size * g.vega;
printf("P&L per 1%% vol move: $%.2f\n", vol_exposure);
```

### Event Trading (Earnings, Fed Meetings)
```cpp
Greeks g = calculate_all(true, S, K, T, r, vol, q);
printf("Pre-event theta burn: $%.4f/day\n", g.theta);
printf("Vol crush impact: $%.4f per 1%% vol drop\n", g.vega);
```

## Important Notes

1. **Delta and Lambda** do not use scaling parameters - they are dimensionless ratios
2. **All other Greeks** accept optional ScalingParams for flexible sensitivity measurement
3. **Scaling defaults** to standard market conventions (daily theta, 1% sensitivities)
4. **Sign conventions** follow standard market practice:
   - Call Delta: 0 to +1, Put Delta: -1 to 0
   - Vega: Always positive for long options
   - Theta: Always negative for long options
   - Rho: Positive for calls, negative for puts
   - Epsilon: Negative for calls, positive for puts