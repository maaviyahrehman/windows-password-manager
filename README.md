# Windows Password Manager

## Overview
Windows Password Manager is a simple console-based application that allows users to generate, encrypt, store, and decrypt passwords securely. The encryption is handled using the Windows Data Protection API (DPAPI), ensuring that passwords remain protected.

## Features
- Generate strong passwords of custom lengths.
- Option to include special characters in passwords.
- Encrypt and securely save generated passwords.
- Decrypt and retrieve stored passwords.
- Uses Windows DPAPI for secure encryption and decryption.

## Requirements
- Windows OS
- C++ Compiler (MinGW/GCC or MSVC)

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/maaviyahrehman/windows-password-manager.git
   cd windows-password-manager
   ```
2. Compile the program using a C++ compiler:
   ```sh
   g++ -std=c++11 -o password_manager password_manager.cpp -lcrypt32
   ```

## Usage
1. Run the executable:
   ```sh
   ./windows-password-manager.exe
   ```
2. Choose an option:
   - `1`: Generate & Save Password
   - `2`: View Decrypted Password
3. Follow the prompts to generate a password and save it securely or retrieve a stored password.

## Example
```
1. Generate & Save Password
2. View Decrypted Password
Choose an option: 1
Enter password length (4, 8, 16, or custom): 16
Include special characters? (1 for Yes, 0 for No): 1
Generated Password: aB!@7dX*eW&1zP4Q
Password saved securely!
```

## File Structure
- `password_manager.cpp` - Main program file
- `passwords.enc` - Encrypted file storing passwords

## Security Notes
- Passwords are encrypted using Windows DPAPI, making them accessible only on the same machine.
- Do not share `passwords.enc` file with others as it is tied to your Windows system.

## License
This project is licensed under the MIT License.

## Contribution
Feel free to contribute by submitting issues or pull requests.

