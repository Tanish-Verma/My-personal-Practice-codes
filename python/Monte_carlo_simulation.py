import numpy as np
import matplotlib.pyplot as plt
import yfinance as yf

# Prompt user for stock symbol and validate input
stock_symbol = input("Enter the stock symbol (e.g., TATAMOTORS.NS): ").strip()
if not stock_symbol:
    raise ValueError("Stock symbol cannot be empty.")

# Download historical data for the specified stock with adjusted prices
# Use a valid end date (today's date or earlier)
print(f"Downloading data for {stock_symbol}...")
data = yf.download(stock_symbol, start='2010-01-01', end='2025-05-01', auto_adjust=True, progress=False)
if data.empty:
    raise ValueError(f"No data downloaded for {stock_symbol}. Please check the stock symbol or date range.")

# Calculate daily log returns using the formula: log(S_t / S_(t-1))
log_returns = np.log(data['Close'] / data['Close'].shift(1)).dropna()

# Estimate daily mean and standard deviation of returns
mu_daily = log_returns.mean()  # Mean of daily log returns
mu = (mu_daily * 252).item()  # Annualized return: μ = μ_daily * 252 (252 trading days in a year)
sigma_daily = log_returns.std()  # Standard deviation of daily log returns
sigma = (sigma_daily * np.sqrt(252)).item()  # Annualized volatility: σ = σ_daily * sqrt(252)

# Get the latest closing price (S₀)
S0 = data['Close'].iloc[-1].item()

# Function to simulate Geometric Brownian Motion (GBM) for stock price paths
def simulate_gbm(S0, mu, sigma, days=252, simulations=1000):
    """
    Simulates stock price paths using the Geometric Brownian Motion (GBM) model.

    Parameters:
    - S0: Initial stock price
    - mu: Expected annual return
    - sigma: Annual volatility
    - days: Number of trading days to simulate
    - simulations: Number of simulation paths

    Returns:
    - price_paths: Simulated stock price paths
    """
    dt = 1 / days  # Time step: Δt = 1 / number of trading days
    drift = (mu - 0.5 * sigma**2) * dt  # Drift term: (μ - 0.5 * σ^2) * Δt
    volatility = sigma * np.sqrt(dt)  # Volatility term: σ * sqrt(Δt)
    random_shocks = np.random.normal(size=(days, simulations))  # Random shocks from a normal distribution
    daily_returns = np.exp(drift + volatility * random_shocks)  # Daily returns: exp(drift + volatility * random_shocks)
    price_paths = S0 * daily_returns.cumprod(axis=0)  # Price paths: S_t = S_(t-1) * exp(daily_returns)
    return price_paths

# Run simulation
paths = simulate_gbm(S0, mu, sigma)

# Plot simulated price paths
plt.figure(figsize=(12, 6))
plt.plot(paths)
plt.title(f"{stock_symbol}: 1,000 Simulated Price Paths")
plt.xlabel("Trading Days")
plt.ylabel("Price (INR)")
plt.show()

# Plot histogram of terminal prices
plt.figure(figsize=(12, 6))
plt.hist(paths[-1], bins=50, density=True, alpha=0.7)
plt.title(f"Terminal Price Distribution After 1 Year for {stock_symbol}")
plt.xlabel("Price (INR)")
plt.ylabel("Probability Density")
plt.show()

# Calculate and print expected price and 95% confidence interval
final_prices = paths[-1]
expected_price = np.mean(final_prices)  # Expected price: mean of terminal prices
conf_interval = np.percentile(final_prices, [2.5, 97.5])  # 95% confidence interval: 2.5th and 97.5th percentiles
price_increase_count = np.sum(final_prices > S0)
probability_increase = (price_increase_count / 1000) * 100  # Convert to percentage

print(f"Expected Price: ₹{expected_price:.2f}")
print(f"95% Confidence Interval: ₹{conf_interval[0]:.2f} - ₹{conf_interval[1]:.2f}")
print(f"Probability of Price Increase: {probability_increase:.1f}%")

# Print the input parameters for reporting
print("\nModel Parameters:")
print(f"Stock Symbol: {stock_symbol}")
print(f"Initial Stock Price (S₀): ₹{S0:.2f}")
print(f"Expected Annual Return (μ): {mu:.4f} ({mu*100:.2f}%)")
print(f"Annual Volatility (σ): {sigma:.4f} ({sigma*100:.2f}%)")
print(f"Time Horizon: 1 year")
print(f"Number of Simulations: 1,000")