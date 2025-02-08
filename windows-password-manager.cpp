//Author: Maaviyah Rehman
//Department: Faculty Of Computing
//Program: BS Data Science
//Project: Password Manager

#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <string>
#include <random>

using namespace std;

string generatePassword(int length, bool includeSpecial) {
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (includeSpecial) {
        chars += "!@#$%^&*()-_=+[]{}|;:'\",.<>?/";
    }
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, chars.size() - 1);

    string password;
    for (int i = 0; i < length; ++i) {
        password += chars[distribution(generator)];
    }
    return password;
}

bool encryptAndSave(const string &password, const string &filename) {
    DATA_BLOB input, output;
    input.pbData = (BYTE*)password.c_str();
    input.cbData = password.size() + 1;

    if (CryptProtectData(&input, L"Password", NULL, NULL, NULL, 0, &output)) {
        ofstream file(filename, ios::binary);
        file.write((char*)output.pbData, output.cbData);
        file.close();
        LocalFree(output.pbData);
        return true;
    }
    return false;
}

bool decryptAndLoad(const string &filename, string &password) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) return false;

    streamsize size = file.tellg();
    file.seekg(0, ios::beg);
    vector<char> buffer(size);
    file.read(buffer.data(), size);
    file.close();

    DATA_BLOB input, output;
    input.pbData = (BYTE*)buffer.data();
    input.cbData = size;

    if (CryptUnprotectData(&input, NULL, NULL, NULL, NULL, 0, &output)) {
        password = string((char*)output.pbData);
        LocalFree(output.pbData);
        return true;
    }
    return false;
}

int main() {
    int choice;
    cout << "1. Generate & Save Password\n2. View Decrypted Password\nChoose an option: ";
    cin >> choice;

    if (choice == 1) {
        int length;
        bool specialChars;
        cout << "Enter password length (4, 8, 16, or custom): ";
        cin >> length;
        cout << "Include special characters? (1 for Yes, 0 for No): ";
        cin >> specialChars;

        string password = generatePassword(length, specialChars);
        cout << "Generated Password: " << password << endl;
        
        if (encryptAndSave(password, "passwords.enc")) {
            cout << "Password saved securely!\n";
        } else {
            cout << "Failed to save password.\n";
        }
    } 
    else if (choice == 2) {
        string decryptedPassword;
        if (decryptAndLoad("passwords.enc", decryptedPassword)) {
            cout << "Decrypted Password: " << decryptedPassword << endl;
        } else {
            cout << "Failed to decrypt password.\n";
        }
    }
    return 0;
}

