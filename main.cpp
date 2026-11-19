#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Structure to hold credential details (Module: Password Manager)
struct Credential {
    string siteName;
    string username;
    string password;
};

// Simple XOR Cipher function to represent the "Encryption Module" for a 2nd year level
string encryptDecrypt(string data) {
    char key = 'K'; // Simple cryptographic key
    string output = data;
    for (size_t i = 0; i < data.size(); i++) {
        output[i] = data[i] ^ key; // XOR operation obfuscates the password
    }
    return output;
}

// Module: Password Generator
string generatePassword(int length) {
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#$!";
    string password = "";
    for (int i = 0; i < length; i++) {
        password += chars[rand() % chars.length()];
    }
    return password;
}

int main() {
    srand(time(0)); // Seed for random password generator
    
    string masterPassword = "";
    string inputPassword;
    vector<Credential> vault;

    cout << "========================================\n";
    cout << "   SECURE VAULT - CONSOLE PROTOTYPE     \n";
    cout << "========================================\n\n";

    // Step 1: Initialize Master Password
    cout << "[Setup] Set your Master Password: ";
    cin >> masterPassword;
    cout << "Master Password saved successfully!\n\n";

    // Step 2: Authentication Module
    cout << "----------------------------------------\n";
    cout << "LOGIN TO SECURE VAULT\n";
    cout << "----------------------------------------\n";
    cout << "Enter Master Password to unlock: ";
    cin >> inputPassword;

    if (inputPassword != masterPassword) {
        cout << "[Error] Incorrect Master Password! Access Denied.\n";
        return 0; // Exit program if authentication fails
    }

    cout << "\n[Success] Access Granted! Welcome to your Secure Vault.\n";

    int choice;
    do {
        // Dashboard Menu
        cout << "\n================ MAIN DASHBOARD ================\n";
        cout << "1. Add New Credential\n";
        cout << "2. View Stored Credentials (Decrypted)\n";
        cout << "3. Generate Strong Password\n";
        cout << "4. Exit / Secure Logout\n";
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Credential c;
                cout << "\nEnter Website/App Name: ";
                cin >> c.siteName;
                cout << "Enter Username: ";
                cin >> c.username;
                cout << "Enter Password: ";
                cin >> c.password;

                // Encrypt password before storing in vector list
                c.password = encryptDecrypt(c.password);
                vault.push_back(c);
                
                cout << "[Success] Credential encrypted and securely stored!\n";
                break;
            }
            case 2: {
                if (vault.empty()) {
                    cout << "\n[Info] Your vault is currently empty.\n";
                } else {
                    cout << "\n--------------- SAVED VAULT RECORDS ---------------\n";
                    for (size_t i = 0; i < vault.size(); i++) {
                        // Decrypt password on-the-fly for the authenticated user
                        string decryptedPassword = encryptDecrypt(vault[i].password);
                        cout << i + 1 << ". Site: " << vault[i].siteName 
                             << " | Username: " << vault[i].username 
                             << " | Password: " << decryptedPassword << "\n";
                    }
                    cout << "---------------------------------------------------\n";
                }
                break;
            }
            case 3: {
                int len;
                cout << "\nEnter desired password length (e.g., 10-16): ";
                cin >> len;
                if (len < 6) {
                    cout << "[Warning] Length too short. Using default length of 8.\n";
                    len = 8;
                }
                string strongPassword = generatePassword(len);
                cout << "[Generated Password]: " << strongPassword << "\n";
                break;
            }
            case 4:
                cout << "\n[Logout] Logging out securely and wiping active session. Goodbye!\n";
                break;
            default:
                cout << "\n[Error] Invalid choice. Please select between 1 and 4.\n";
        }
    } while (choice != 4);

    return 0;
}