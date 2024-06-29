#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>  // Required for std::find_if
#include <sstream>    // Required for stringstream

using namespace std;

class Expense;

class User {
public:
    int id;
    string name;
    float balance;
    vector<Expense*> expenses_paid_for;

    User(int _id, string _name) : id(_id), name(_name), balance(0) {}

    bool operator<(const User& other) const {
        return balance < other.balance;
    }
};

class Expense {
public:
    int id;
    float amount;
    User* paid_by;
    vector<User*> participants;

    Expense(int _id, float _amount, User* _paid_by, const vector<User*>& _participants) 
        : id(_id), amount(_amount), paid_by(_paid_by), participants(_participants) {}
};

void add_expense(vector<User>& users, vector<Expense*>& expenses, int paid_by_id, float amount, const vector<int>& participant_ids) {
    User* paid_by = nullptr;
    for (auto& user : users) {
        if (user.id == paid_by_id) {
            paid_by = &user;
            break;
        }
    }

    if (!paid_by) {
        cout << "User with ID " << paid_by_id << " not found." << endl;
        return;
    }

    vector<User*> participants;
    for (int id : participant_ids) {
        auto it = find_if(users.begin(), users.end(), [id](const User& user) { return user.id == id; });
        if (it != users.end()) {
            participants.push_back(&(*it));
        } else {
            cout << "Participant with ID " << id << " not found." << endl;
            return;
        }
    }

    Expense* expense = new Expense(expenses.size() + 1, amount, paid_by, participants);
    expenses.push_back(expense);

    float total_amount = expense->amount;
    float per_person_share = total_amount / expense->participants.size();

    expense->paid_by->balance -= total_amount;
    for (User* participant : expense->participants) {
        if (participant != expense->paid_by) {
            participant->balance += per_person_share;
        }
    }
    expense->paid_by->expenses_paid_for.push_back(expense);
}

void print_balances(const vector<User>& users) {
    for (const auto& user : users) {
        cout << user.name << ": " << user.balance << endl;
    }
}

vector<tuple<User*, User*, float>> optimize_debts(vector<User>& users) {
    vector<tuple<User*, User*, float>> transactions;
    priority_queue<User*> max_heap;
    priority_queue<User*> min_heap;

    for (User& user : users) {
        if (user.balance < 0) {
            max_heap.push(&user);
        } else if (user.balance > 0) {
            min_heap.push(&user);
        }
    }

    while (!max_heap.empty() && !min_heap.empty()) {
        User* debtor = max_heap.top();
        max_heap.pop();

        User* creditor = min_heap.top();
        min_heap.pop();

        float amount_settled = min(-debtor->balance, creditor->balance);
        transactions.push_back(make_tuple(debtor, creditor, amount_settled));

        debtor->balance += amount_settled;
        creditor->balance -= amount_settled;

        if (debtor->balance < 0) {
            max_heap.push(debtor);
        }
        if (creditor->balance > 0) {
            min_heap.push(creditor);
        }
    }

    return transactions;
}

void handle_user_input(vector<User>& users, vector<Expense*>& expenses) {
    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Add Expense" << endl;
        cout << "2. Print Balances" << endl;
        cout << "3. Optimize Debts" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int paid_by_id;
                float amount;
                vector<int> participant_ids;
                string input;

                cout << "Enter ID of user who paid: ";
                cin >> paid_by_id;

                cout << "Enter amount of the expense: ";
                cin >> amount;

                cout << "Enter IDs of participants (comma-separated): ";
                cin.ignore();  // Clear the input buffer
                getline(cin, input);
                stringstream ss(input);
                string temp;
                while (getline(ss, temp, ',')) {
                    participant_ids.push_back(stoi(temp));
                }

                add_expense(users, expenses, paid_by_id, amount, participant_ids);
                break;
            }
            case 2:
                cout << "\nCurrent Balances:" << endl;
                print_balances(users);
                break;
            case 3: {
                cout << "\nOptimizing Debts..." << endl;
                auto transactions = optimize_debts(users);

                cout << "\nOptimized Debt Settlements:" << endl;
                for (const auto& transaction : transactions) {
                    cout << get<1>(transaction)->name << " pays " << get<0>(transaction)->name
                         << " $" << get<2>(transaction) << endl;
                }
                break;
            }
            case 4:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }
    }
}

int main() {
    // Sample users
    vector<User> users = {
        User(1, "Alice"),
        User(2, "Bob"),
        User(3, "Charlie"),
        User(4, "David")
    };

    // List to store expenses
    vector<Expense*> expenses;

    // Handle user input and interactions
    handle_user_input(users, expenses);

    // Clean up allocated memory for expenses
    for (Expense* expense : expenses) {
        delete expense;
    }

    return 0;
}




