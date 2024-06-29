import pandas as pd
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score

# Load train.csv
train_data = pd.read_csv('train.csv')

# Selecting relevant columns
selected_columns = ['GrLivArea', 'BedroomAbvGr', 'FullBath', 'HalfBath', 'SalePrice']
data = train_data[selected_columns].copy()

# Check for any missing values
print("Missing values:")
print(data.isnull().sum())

# Features (X) and Target (y)
X = data.drop(columns=['SalePrice'])
y = data['SalePrice']

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Initialize the Linear Regression model
model = LinearRegression()

# Fit the model on the training data
model.fit(X_train, y_train)

# Predict on the testing data
y_pred = model.predict(X_test)

# Evaluate the model
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)

print(f"\nMean Squared Error (MSE): {mse}")
print(f"R-squared (R2): {r2}")

# Example prediction for a new data point
new_data = pd.DataFrame({
    'GrLivArea': [2000],
    'BedroomAbvGr': [3],
    'FullBath': [2],
    'HalfBath': [1]
})

predicted_price = model.predict(new_data)
print(f"\nPredicted Price for new data point: ${predicted_price[0]:,.2f}")
