#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfContact;
    string phoneNumber;
    int frequency;  // To store the frequency of queries for this contact

    TrieNode() : isEndOfContact(false), frequency(0) {}
};

class Trie {
private:
    TrieNode* root;

    void toLowerCase(string &str) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    void autoCompleteHelper(TrieNode* current, string prefix, vector<pair<string, pair<string, int>>>& results) {
        if (current->isEndOfContact) {
            results.emplace_back(prefix, make_pair(current->phoneNumber, current->frequency));
        }

        for (const auto& pair : current->children) {
            autoCompleteHelper(pair.second, prefix + pair.first, results);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& name, const string& phoneNumber) {
        string nameLower = name;
        toLowerCase(nameLower);
        TrieNode* current = root;
        for (char ch : nameLower) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfContact = true;
        current->phoneNumber = phoneNumber;
    }

    TrieNode* searchNode(const string& prefix) {
        string prefixLower = prefix;
        toLowerCase(prefixLower);
        TrieNode* current = root;
        for (char ch : prefixLower) {
            if (current->children.find(ch) == current->children.end()) {
                return nullptr;
            }
            current = current->children[ch];
        }
        current->frequency++;
        return current;
    }

    vector<pair<string, pair<string, int>>> autoComplete(const string& prefix) {
        vector<pair<string, pair<string, int>>> results;
        TrieNode* current = searchNode(prefix);

        if (current != nullptr) {
            autoCompleteHelper(current, prefix, results);
        }

        // Sort results by frequency in descending order
        sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
            return b.second.second < a.second.second;
        });

        return results;
    }
};

int main() {
    Trie phonebook;
    phonebook.insert("Alice", "123-456-7890");
    phonebook.insert("Bob", "234-567-8901");
    phonebook.insert("Charlie", "345-678-9012");
    phonebook.insert("David", "456-789-0123");
    phonebook.insert("Eve", "567-890-1234");
    phonebook.insert("Allan", "678-901-2345");
    phonebook.insert("Chris", "789-012-3456");
    phonebook.insert("Christina", "890-123-4567");
    phonebook.insert("Albert", "901-234-5678");
    phonebook.insert("Daniel", "012-345-6789");

    string prefix;
    while (true) {
        cout << "Enter the prefix to search in the phonebook (or type 'exit' to quit): ";
        cin >> prefix;
        if (prefix == "exit") {
            break;
        }

        vector<pair<string, pair<string, int>>> suggestions = phonebook.autoComplete(prefix);

        cout << "Phonebook entries matching \"" << prefix << "\":" << endl;
        for (const auto& entry : suggestions) {
            cout << "Name: " << entry.first << ", Phone Number: " << entry.second.first << ", Frequency: " << entry.second.second << endl;
        }
    }

    return 0;
}
