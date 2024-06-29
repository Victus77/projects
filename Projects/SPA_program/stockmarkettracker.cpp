#include <iostream>
#include <vector>
#include <numeric> // for accumulate
#include <deque>
#include <algorithm> // for max_element
#include <fstream> // for file handling
#include <cmath> // for abs

using namespace std;

// Function to calculate simple moving average
vector<double> calculateMovingAverage(const vector<double>& prices, int period) {
    vector<double> movingAverages;
    double sum = 0.0;
    for (int i = 0; i < prices.size(); ++i) {
        sum += prices[i];
        if (i >= period - 1) {
            if (i >= period) sum -= prices[i - period];
            movingAverages.push_back(sum / period);
        }
    }
    return movingAverages;
}

// Function to calculate exponential moving average
vector<double> calculateEMA(const vector<double>& prices, int period) {
    vector<double> ema;
    double multiplier = 2.0 / (period + 1);
    ema.push_back(prices[0]); // First EMA is the first price
    for (int i = 1; i < prices.size(); ++i) {
        double value = ((prices[i] - ema.back()) * multiplier) + ema.back();
        ema.push_back(value);
    }
    return ema;
}

// Function to detect peaks
vector<int> findPeaks(const vector<double>& prices) {
    vector<int> peaks;
    for (int i = 1; i < prices.size() - 1; ++i) {
        if (prices[i] > prices[i - 1] && prices[i] > prices[i + 1]) {
            peaks.push_back(i);
        }
    }
    return peaks;
}

// Function to detect head and shoulders pattern (simplified)
bool detectHeadAndShoulders(const vector<double>& prices) {
    for (int i = 1; i < prices.size() - 2; ++i) {
        if (prices[i - 1] < prices[i] && prices[i] > prices[i + 1] &&
            prices[i + 1] < prices[i + 2]) {
            return true;
        }
    }
    return false;
}

// Function to display stock prices
void displayPrices(const vector<double>& prices) {
    for (double price : prices) {
        cout << price << " ";
    }
    cout << endl;
}

// Function to display moving averages
void displayMovingAverages(const vector<double>& movingAverages) {
    for (double avg : movingAverages) {
        cout << avg << " ";
    }
    cout << endl;
}

// Function to display peaks
void displayPeaks(const vector<int>& peaks) {
    cout << "Peaks at indices: ";
    for (int index : peaks) {
        cout << index << " ";
    }
    cout << endl;
}

int main() {
    // Read stock prices from file
    ifstream inputFile("stock_prices.txt");
    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    vector<double> stockPrices;
    double price;
    while (inputFile >> price) {
        stockPrices.push_back(price);
    }
    inputFile.close();

    int period = 3;

    cout << "Stock Prices: ";
    displayPrices(stockPrices);

    vector<double> movingAverages = calculateMovingAverage(stockPrices, period);
    cout << "Moving Averages (Period = " << period << "): ";
    displayMovingAverages(movingAverages);

    vector<double> ema = calculateEMA(stockPrices, period);
    cout << "Exponential Moving Averages (Period = " << period << "): ";
    displayMovingAverages(ema);

    vector<int> peaks = findPeaks(stockPrices);
    displayPeaks(peaks);

    bool hasHeadAndShoulders = detectHeadAndShoulders(stockPrices);
    cout << "Head and Shoulders pattern detected: " << (hasHeadAndShoulders ? "Yes" : "No") << endl;

    // Write results to file
    ofstream outputFile("analysis_results.txt");
    if (outputFile) {
        outputFile << "Stock Prices: ";
        for (double price : stockPrices) {
            outputFile << price << " ";
        }
        outputFile << endl;

        outputFile << "Moving Averages (Period = " << period << "): ";
        for (double avg : movingAverages) {
            outputFile << avg << " ";
        }
        outputFile << endl;

        outputFile << "Exponential Moving Averages (Period = " << period << "): ";
        for (double e : ema) {
            outputFile << e << " ";
        }
        outputFile << endl;

        outputFile << "Peaks at indices: ";
        for (int index : peaks) {
            outputFile << index << " ";
        }
        outputFile << endl;

        outputFile << "Head and Shoulders pattern detected: " << (hasHeadAndShoulders ? "Yes" : "No") << endl;

        outputFile.close();
    } else {
        cerr << "Error writing to file!" << endl;
    }

    return 0;
}

