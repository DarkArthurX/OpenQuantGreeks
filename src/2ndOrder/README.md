# Second Order Greeks - Rate of Change

Second order Greeks tell you how your first order Greeks change when market conditions shift. They're the "speedometer for your speedometer" - essential for understanding how your option's behavior will evolve as markets move.

Think of them as early warning systems that help you anticipate changes in your risk profile before they happen.

## Why Second Order Greeks Matter

First order Greeks tell you your current exposure, but they don't tell you how that exposure will change. Second order Greeks fill that gap:

- **Dynamic hedging**: Know when your hedges will need adjustment
- **Volatility trading**: Understand how your vega exposure changes with volatility itself
- **Time management**: Predict how your Greeks decay as expiration approaches
- **Risk control**: Anticipate accelerating losses or gains

## The Greeks Explained

### Gamma (Γ) - Rate of Change of Delta
**What it measures**: How much your Delta changes when the stock price moves $1.

**Think of it as**: The "acceleration" of your option's price movement.

**Practical examples**:
- Gamma = 0.05 means if stock moves up $1, your Delta increases by 0.05
- High Gamma: Delta changes rapidly (good for big moves, bad for hedging costs)
- Low Gamma: Delta changes slowly (stable hedging, limited upside)

**Trading insights**:
- **Long Gamma** (buying options): You want big price moves in either direction
- **Short Gamma** (selling options): You want the stock to stay put
- Gamma highest for at-the-money options near expiration

```cpp
double gamma = calculate_gamma(100, 100, 0.25, 0.05, 0.20, 0.02);
printf("Delta changes by %.4f per $1 stock move\n", gamma);

// High gamma near expiration
double gamma_short = calculate_gamma(100, 100, 0.05, 0.05, 0.20, 0.02);  // 2 weeks
printf("Near expiry gamma: %.4f (watch for rapid delta changes)\n", gamma_short);
```

### Vanna - Delta's Sensitivity to Volatility
**What it measures**: How much your Delta changes when volatility changes by 1%.

**Think of it as**: The link between price direction and volatility changes.

**Practical examples**:
- Vanna = 0.02 means if volatility rises from 20% to 21%, your Delta increases by 0.02
- Important during market stress when volatility and price often move together
- Can cause unexpected P&L when volatility spikes during price moves

**Trading insights**:
- **Positive Vanna**: Delta increases with volatility (good during vol spikes)
- **Negative Vanna**: Delta decreases with volatility (bad during vol spikes)
- Critical for managing positions during earnings or news events

```cpp
// Standard: per 1% volatility change
double vanna = calculate_vanna(100, 105, 0.25, 0.05, 0.20, 0.02);

// Precise: per 0.1% volatility change for fine-tuned hedging
ScalingParams precise;
precise.vega_scale = 1000.0;
double vanna_10bp = calculate_vanna(100, 105, 0.25, 0.05, 0.20, 0.02, precise);
printf("Delta changes by %.4f per 10bp vol move\n", vanna_10bp);
```

### Charm - Delta Decay (Delta's Sensitivity to Time)
**What it measures**: How much your Delta changes each day due to time passing.

**Think of it as**: The "aging" of your option's directional exposure.

**Practical examples**:
- Charm = -0.03 means your Delta decreases by 0.03 each day
- For calls: Usually negative (Delta decays toward 0 or 1)
- For puts: Can be positive or negative depending on moneyness

**Trading insights**:
- High Charm: Your directional exposure changes rapidly over time
- Plan hedge adjustments based on expected charm decay
- Most important for weekly options where time decay accelerates

```cpp
// Daily charm decay
double charm = calculate_charm(true, 100, 110, 0.25, 0.05, 0.20, 0.02);

// Intraday trading: annual charm (no daily scaling)
double charm_annual = calculate_charm(true, 100, 110, 0.25, 0.05, 0.20, 0.02,
                                    ScalingParams::intraday());
printf("Daily delta decay: %.4f, Annual: %.2f\n", charm, charm_annual);
```

### Volga/Vomma - Vega's Sensitivity to Volatility
**What it measures**: How much your Vega changes when volatility changes by 1%.

**Think of it as**: The "convexity" of your volatility exposure.

**Practical examples**:
- Volga = 0.08 means if volatility rises from 20% to 21%, your Vega increases by 0.08
- Always positive for long options (more vol = higher vega)
- Critical for volatility trading strategies

**Trading insights**:
- **Long Volga**: Benefits from large volatility moves in either direction
- **Short Volga**: Wants volatility to stay stable
- Highest for at-the-money options with moderate time to expiration

```cpp
double volga = calculate_volga(100, 100, 0.25, 0.05, 0.20, 0.02);
printf("Vega changes by %.4f per 1%% vol move\n", volga);

// For volatility term structure plays
printf("Volga convexity: %.4f (positive = benefits from vol of vol)\n", volga);
```

### Veta - Vega Decay (Vega's Sensitivity to Time)
**What it measures**: How much your Vega decreases each day due to time passing.

**Think of it as**: How your volatility exposure "evaporates" over time.

**Practical examples**:
- Veta = -0.12 means your Vega decreases by 0.12 each day
- Always negative (Vega decays to zero at expiration)
- Accelerates as expiration approaches

**Trading insights**:
- Plan volatility trades knowing your Vega will decay
- High Veta positions need volatility moves soon
- Consider rolling positions to maintain Vega exposure

```cpp
double veta = calculate_veta(100, 100, 0.25, 0.05, 0.20, 0.02);
printf("Vega decays by %.4f per day\n", veta);
```

### Vera - Vega's Sensitivity to Interest Rates
**What it measures**: How much your Vega changes when interest rates change by 1%.

**Think of it as**: The intersection of volatility and rate sensitivity.

**Practical examples**:
- Vera = 0.05 means if rates rise from 5% to 6%, your Vega increases by 0.05
- Generally small but can matter for long-dated options
- Important during Fed meetings or rate cycle changes

```cpp
double vera = calculate_vera(100, 100, 1.0, 0.05, 0.20, 0.02);  // 1-year option
printf("Vega changes by %.4f per 1%% rate move\n", vera);
```

### Dual Rho - Rho's Sensitivity to Interest Rates
**What it measures**: How much your Rho changes when interest rates change by 1%.

**Think of it as**: The "convexity" of your interest rate exposure.

**Practical examples**:
- Dual Rho = 0.03 means if rates rise from 5% to 6%, your Rho increases by 0.03
- Mainly relevant for very long-dated options
- Can be important for LEAPS and long-term strategies

```cpp
double dual_rho = calculate_dual_rho(100, 100, 2.0, 0.05, 0.20, 0.02);  // 2-year LEAP
printf("Rho changes by %.4f per 1%% rate move\n", dual_rho);
```

## Scaling Configurations

All second order Greeks support configurable scaling based on their underlying sensitivities:

```cpp
// Standard scaling
ScalingParams standard = ScalingParams::standard();

// Intraday trading - no time scaling for charm
ScalingParams intraday = ScalingParams::intraday();

// High precision - 0.1% sensitivity measures
ScalingParams precise;
precise.vega_scale = 1000.0;  // Vanna, Volga, Veta, Vera use this
precise.rho_scale = 10000.0;  // Dual Rho uses this

// Custom time scaling
ScalingParams custom;
custom.charm_scale = 252.0;   // Business days instead of calendar days
```

## Trading Strategies Using Second Order Greeks

### Gamma Scalping
```cpp
Greeks g = calculate_all(true, S, K, T, r, vol, q);
double gamma_pnl_per_move = 0.5 * g.gamma * position_size;
printf("P&L from $1 move then revert: $%.2f\n", gamma_pnl_per_move);
```

### Volatility Convexity Plays
```cpp
Greeks g = calculate_all(true, S, K, T, r, vol, q);
double vol_convexity = position_size * g.volga;
printf("Benefits from vol-of-vol: $%.4f per 1%% vol²\n", vol_convexity);
```

### Dynamic Hedge Monitoring
```cpp
Greeks g = calculate_all(true, S, K, T, r, vol, q);
printf("Tomorrow's expected delta: %.4f\n", g.delta + g.charm);
printf("Delta after 1%% vol spike: %.4f\n", g.delta + g.vanna);
printf("Hedge adjustment needed if stock moves $2: %.4f shares\n", 2.0 * g.gamma);
```

## Key Relationships

**Gamma and Theta**: Generally related by Gamma ≈ -Theta / (0.5 × S² × σ²)
**Vanna symmetry**: ∂Delta/∂σ = ∂Vega/∂S
**Time decay acceleration**: All time-related Greeks accelerate near expiration

## Production Usage Notes

1. **Gamma hedging** requires frequent rebalancing - monitor transaction costs
2. **Vanna exposure** can cause unexpected P&L during correlated vol/price moves  
3. **Charm planning** helps anticipate when hedge ratios need adjustment
4. **Volga trading** works best in high-volatility environments
5. **Time Greeks** (Charm, Veta) become crucial in the final weeks before expiration

Second order Greeks are essential for sophisticated options trading and risk management. They transform you from reactive to proactive in managing your positions.