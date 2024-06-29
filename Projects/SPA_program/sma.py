import yfinance as yf
import pandas as pd
import plotly.graph_objects as go

# Function to fetch intraday stock data
def fetch_stock_data(ticker, start_date, end_date, interval='1d'):
    stock = yf.Ticker(ticker)
    df = stock.history(start=start_date, end=end_date, interval=interval)
    return df

# Function to calculate Simple Moving Average (SMA)
def calculate_sma(prices, period):
    return prices.rolling(window=period).mean()

# Function to calculate Exponential Moving Average (EMA)
def calculate_ema(prices, period):
    return prices.ewm(span=period, adjust=False).mean()

# Function to calculate Relative Strength Index (RSI)
def calculate_rsi(prices, period):
    delta = prices.diff()
    gain = (delta.where(delta > 0, 0)).rolling(window=period).mean()
    loss = (-delta.where(delta < 0, 0)).rolling(window=period).mean()
    rs = gain / loss
    return 100 - (100 / (1 + rs))

# Function to plot stock data and indicators
def plot_stock_data(df, sma, ema, rsi, ticker):
    fig = go.Figure()

    # Plot stock prices
    fig.add_trace(go.Scatter(x=df.index, y=df['Close'], mode='lines', name='Close'))

    # Plot SMA
    fig.add_trace(go.Scatter(x=df.index, y=sma, mode='lines', name='SMA'))

    # Plot EMA
    fig.add_trace(go.Scatter(x=df.index, y=ema, mode='lines', name='EMA'))

    # Plot RSI
    fig.add_trace(go.Scatter(x=df.index, y=rsi, mode='lines', name='RSI', yaxis='y2'))

    # Update layout
    fig.update_layout(
        title=f'Stock Market Analyzer for {ticker}',
        xaxis_title='Time',
        yaxis_title='Price',
        yaxis2=dict(
            title='RSI',
            overlaying='y',
            side='right',
            range=[0, 100]
        ),
        legend=dict(x=0, y=1),
        xaxis_rangeslider_visible=False
    )

    fig.show()

def main():
    # User inputs
    ticker = input("Enter the stock ticker symbol (e.g., AAPL, MSFT): ")
    start_date = input("Enter the start date (YYYY-MM-DD): ")
    end_date = input("Enter the end date (YYYY-MM-DD): ")

    # Parameters for technical indicators
    sma_period = 20
    ema_period = 20
    rsi_period = 14

    # Fetch intraday stock data (1-minute interval)
    df = fetch_stock_data(ticker, start_date, end_date, interval='1d')

    # Calculate technical indicators
    sma = calculate_sma(df['Close'], sma_period)
    ema = calculate_ema(df['Close'], ema_period)
    rsi = calculate_rsi(df['Close'], rsi_period)

    # Plot data and indicators
    plot_stock_data(df, sma, ema, rsi, ticker)

if __name__ == '__main__':
    main()


