import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, r2_score

# Load train and test data
train_data = pd.read_csv('train.csv')
test_data = pd.read_csv('test.csv')

# Combine train and test data for preprocessing
all_data = pd.concat([train_data.drop(columns=['SalePrice']), test_data], axis=0, ignore_index=True)

# Display information about the dataset
print(train_data.info())

# Check for missing values
print("Missing values in train set:")
print(train_data.isnull().sum())

# Check for missing values in test set
print("Missing values in test set:")
print(test_data.isnull().sum())

# Preprocessing: Handle missing values
# For numerical columns, fill with median
numeric_cols = all_data.select_dtypes(include=np.number).columns.tolist()
all_data[numeric_cols] = all_data[numeric_cols].fillna(all_data[numeric_cols].median())

# For categorical columns, fill with mode (if any)
categorical_cols = all_data.select_dtypes(exclude=np.number).columns.tolist()
all_data[categorical_cols] = all_data[categorical_cols].fillna(all_data[categorical_cols].mode().iloc[0])

# One-hot encode categorical variables
all_data = pd.get_dummies(all_data, drop_first=True)

# Split data back into train and test sets
X_train = all_data.iloc[:train_data.shape[0]]
X_test = all_data.iloc[train_data.shape[0]:]
y_train = train_data['SalePrice']

# Split the training data into train and validation sets
X_train_split, X_val, y_train_split, y_val = train_test_split(X_train, y_train, test_size=0.2, random_state=42)

# Initialize the Linear Regression model
model = LinearRegression()

# Fit the model on the training data
model.fit(X_train_split, y_train_split)

# Predict on the validation data
y_val_pred = model.predict(X_val)

# Evaluate the model
mse = mean_squared_error(y_val, y_val_pred)
r2 = r2_score(y_val, y_val_pred)

print(f"\nMean Squared Error (MSE) on validation set: {mse:.2f}")
print(f"R-squared (R2) on validation set: {r2:.4f}")

# Plotting actual vs predicted prices
plt.figure(figsize=(10, 6))
plt.scatter(y_val, y_val_pred, color='blue', alpha=0.6)
plt.plot([min(y_val), max(y_val)], [min(y_val), max(y_val)], color='red', linestyle='--')
plt.xlabel('Actual Price')
plt.ylabel('Predicted Price')
plt.title('Actual vs Predicted House Prices')
plt.grid(True)
plt.show()

# Predict on the test data for submission
test_predictions = model.predict(X_test)

# Prepare submission DataFrame
submission = pd.DataFrame({
    "Id": test_data["Id"],
    "SalePrice": test_predictions
})

# Save submission to CSV file
submission.to_csv("submission.csv", index=False)
print("\nSubmission saved successfully.")
