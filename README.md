# OpenQuantGreeks 📈

Welcome to the **OpenQuantGreeks** repository! This library provides a complete collection of the Greeks, from first to sixth order, essential for anyone involved in options trading and financial modeling. You can find the latest releases [here](https://github.com/DarkArthurX/OpenQuantGreeks/releases).

![OpenQuantGreeks](https://img.shields.io/badge/OpenQuantGreeks-v1.0-blue)

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Greeks Overview](#greeks-overview)
   - [Delta](#delta)
   - [Gamma](#gamma)
   - [Theta](#theta)
   - [Vega](#vega)
   - [Rho](#rho)
   - [Charm](#charm)
   - [Epsilon](#epsilon)
6. [Examples](#examples)
7. [Contributing](#contributing)
8. [License](#license)
9. [Contact](#contact)

## Introduction

In the world of options trading, understanding the Greeks is crucial for effective risk management and strategy development. This library simplifies the process of calculating and using the Greeks, allowing traders and analysts to focus on making informed decisions.

## Features

- Comprehensive library covering all Greeks from first to sixth order.
- Easy integration with existing trading systems.
- User-friendly interface for quick calculations.
- Supports various options pricing models.
- Detailed documentation and examples.

## Installation

To install the OpenQuantGreeks library, clone the repository and install the required dependencies. Run the following commands:

```bash
git clone https://github.com/DarkArthurX/OpenQuantGreeks.git
cd OpenQuantGreeks
pip install -r requirements.txt
```

Make sure to check the [Releases](https://github.com/DarkArthurX/OpenQuantGreeks/releases) section for the latest version.

## Usage

After installation, you can import the library into your Python scripts. Here’s a simple example:

```python
from openquantgreeks import Greeks

# Create an instance of the Greeks class
greeks = Greeks(price=100, strike=105, time_to_expiry=30, volatility=0.2, interest_rate=0.05)

# Calculate Delta
delta = greeks.delta()
print(f"Delta: {delta}")
```

## Greeks Overview

### Delta

Delta measures the sensitivity of an option's price to changes in the price of the underlying asset. It ranges from 0 to 1 for call options and -1 to 0 for put options. 

**Formula:**
\[ \Delta = \frac{\partial C}{\partial S} \]

### Gamma

Gamma measures the rate of change of delta as the underlying asset price changes. It helps traders understand how delta will change as market conditions fluctuate.

**Formula:**
\[ \Gamma = \frac{\partial^2 C}{\partial S^2} \]

### Theta

Theta represents the time decay of an option. It quantifies how much the price of an option decreases as it approaches its expiration date.

**Formula:**
\[ \Theta = \frac{\partial C}{\partial t} \]

### Vega

Vega measures an option's sensitivity to changes in the volatility of the underlying asset. It indicates how much the price of an option is expected to change when the volatility increases by 1%.

**Formula:**
\[ \nu = \frac{\partial C}{\partial \sigma} \]

### Rho

Rho measures the sensitivity of an option's price to changes in interest rates. It indicates how much the price of an option is expected to change when interest rates increase by 1%.

**Formula:**
\[ \rho = \frac{\partial C}{\partial r} \]

### Charm

Charm, also known as Delta decay, measures the change in delta over time. It helps traders understand how delta will evolve as the option approaches expiration.

**Formula:**
\[ \text{Charm} = \frac{\partial \Delta}{\partial t} \]

### Epsilon

Epsilon measures the sensitivity of an option's price to changes in the dividend yield of the underlying asset. It helps traders assess the impact of dividend payments on option pricing.

**Formula:**
\[ \epsilon = \frac{\partial C}{\partial q} \]

## Examples

### Example 1: Calculating All Greeks

```python
from openquantgreeks import Greeks

# Initialize parameters
price = 100
strike = 105
time_to_expiry = 30
volatility = 0.2
interest_rate = 0.05

# Create Greeks instance
greeks = Greeks(price, strike, time_to_expiry, volatility, interest_rate)

# Calculate all Greeks
delta = greeks.delta()
gamma = greeks.gamma()
theta = greeks.theta()
vega = greeks.vega()
rho = greeks.rho()
charm = greeks.charm()
epsilon = greeks.epsilon()

# Print results
print(f"Delta: {delta}, Gamma: {gamma}, Theta: {theta}, Vega: {vega}, Rho: {rho}, Charm: {charm}, Epsilon: {epsilon}")
```

### Example 2: Using Greeks in Trading Strategy

```python
from openquantgreeks import Greeks

# Define your option parameters
price = 150
strike = 155
time_to_expiry = 45
volatility = 0.25
interest_rate = 0.03

# Initialize Greeks
greeks = Greeks(price, strike, time_to_expiry, volatility, interest_rate)

# Implement a simple trading strategy based on Delta
if greeks.delta() > 0.5:
    print("Consider buying the call option.")
else:
    print("Consider selling the call option.")
```

## Contributing

We welcome contributions to OpenQuantGreeks! If you have ideas for improvements or new features, please open an issue or submit a pull request. 

### Steps to Contribute:

1. Fork the repository.
2. Create a new branch for your feature or fix.
3. Make your changes and commit them.
4. Push your branch and open a pull request.

## License

OpenQuantGreeks is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact

For any questions or suggestions, please reach out to the repository maintainer:

- **Name:** DarkArthurX
- **Email:** darkarthurx@example.com

Feel free to visit the [Releases](https://github.com/DarkArthurX/OpenQuantGreeks/releases) section for the latest updates and downloads. Thank you for using OpenQuantGreeks!