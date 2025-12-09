#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Check if username already exists in users.txt
bool usernameExists(const string &username) {
    ifstream file("users.txt");

    if (!file.is_open()) {
        return false; // File doesn't exist yet ? no users
    }

    string u, p;
    while (file >> u >> p) {
        if (u == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Registration function
void registerUser() {
    string username, password;

    cout << "\n--- USER REGISTRATION ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Validate empty input
    if (username.empty() || password.empty()) {
        cout << "Error: Username or password cannot be empty.\n";
        return;
    }

    // Check for duplicate username
    if (usernameExists(username)) {
        cout << "Error: Username already exists. Try another.\n";
        return;
    }

    // Save new user to file
    ofstream file("users.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    file << username << " " << password << endl;
    file.close();

    cout << "Registration successful! User saved.\n";
}

// Login function
void loginUser() {
    string username, password;

    cout << "\n--- USER LOGIN ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");

    if (!file.is_open()) {
        cout << "Error: No registered users found.\n";
        return;
    }

    string u, p;
    bool found = false;

    while (file >> u >> p) {
        if (u == username && p == password) {
            found = true;
            break;
        }
    }

    file.close();

    if (found)
        cout << "Login successful! Welcome, " << username << ".\n";
    else
        cout << "Error: Incorrect username or password.\n";
}

int main() {
    int choice;

    while (true) {
        cout << "\n========= MENU =========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input, try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}

