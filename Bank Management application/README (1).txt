Bank Management System - C++ Application

Overview
This is a complete banking application built with C++ that demonstrates object-oriented programming principles and file handling for persistent data storage.


Key Features

1. Account Management
   - Create new accounts with auto-generated account numbers
   - Modify account details (name, PIN)
   - Delete accounts with confirmation
   - View all accounts

2. Banking Operations
   - Deposit money with validation
   - Withdraw money with balance checking
   - Check account balance
   - Real-time balance updates

3. Security Features
   - 4-digit PIN authentication for all transactions
   - Secure file-based storage (binary format)
   - PIN verification before any operation

4. Data Persistence
   - All account data stored in binary file (accounts.dat)
   - Automatic data loading and saving


Object-Oriented Design

The application uses two main classes:

1. Account Class
   - Encapsulates account data (account number, name, balance, PIN)
   - Methods: deposit(), withdraw(), displayAccount(), verifyPIN()
   - Private data members with public getter/setter methods

2. BankSystem Class
   - Manages all banking operations
   - Handles file I/O operations
   - Provides CRUD operations (Create, Read, Update, Delete)


How to Compile and Run

Windows (MinGW/GCC):
   g++ bank_management.cpp -o bank_management.exe
   bank_management.exe

Windows (MSVC):
   cl bank_management.cpp
   bank_management.exe

Linux/Mac:
   g++ bank_management.cpp -o bank_management
   ./bank_management


User Guide

1. Create New Account
   - Select option 1 from main menu
   - Enter account holder name
   - Set a 4-digit PIN (remember this)
   - Enter initial deposit amount
   - System generates unique account number automatically

2. Deposit Money
   - Select option 2
   - Enter your account number
   - Enter your 4-digit PIN
   - Enter deposit amount
   - Confirmation and new balance displayed

3. Withdraw Money
   - Select option 3
   - Enter your account number
   - Enter your 4-digit PIN
   - Enter withdrawal amount
   - System checks for sufficient balance

4. Check Balance
   - Select option 4
   - Enter your account number
   - Enter your 4-digit PIN
   - Complete account details displayed

5. View All Accounts
   - Select option 5
   - Displays list of all accounts with balances

6. Modify Account
   - Select option 6
   - Enter your account number
   - Enter your 4-digit PIN
   - Update name and/or PIN

7. Delete Account
   - Select option 7
   - Enter your account number
   - Enter your 4-digit PIN
   - Confirm deletion


Technical Details

Language: C++ (Standard C++11 or higher)
File Format: Binary (.dat)
Storage File: accounts.dat (created automatically)
Account Number: Auto-incremented starting from 1001
PIN Length: Exactly 4 digits
Currency: Dollar with 2 decimal places


File Structure

The application uses binary file handling for secure data storage. The accounts.dat file stores Account objects with the following fields:
   - accountNumber
   - name
   - balance
   - pin


Security Features

1. PIN Authentication
   All transactions require PIN verification. The 4-digit numeric PIN is stored securely in binary format.

2. Input Validation
   - Negative amounts are rejected
   - Insufficient balance checks
   - PIN length validation
   - Account existence verification

3. Data Integrity
   - Binary file format prevents casual tampering
   - Atomic file operations
   - Confirmation required for destructive operations


Sample Workflow

1. Start the application
2. Create account for "John Doe" with PIN 1234 and initial deposit $1000
   Result: Account number 1001 created
3. Deposit $500 to account 1001
   Result: New balance is $1500
4. Withdraw $300 from account 1001
   Result: New balance is $1200
5. Check balance
   Result: Shows $1200
6. Exit and restart
   Result: All data persists


Testing Checklist

Basic Operations:
- Create multiple accounts
- Deposit different amounts
- Withdraw with sufficient balance
- Try to withdraw more than balance (should fail)
- Enter wrong PIN (should deny access)
- Check balance displays correctly

Account Management:
- Modify account name
- Change PIN
- Delete account with confirmation
- View all accounts list

Data Persistence:
- Exit and restart application
- Verify all data persists correctly


Common Issues and Solutions

Problem: Program crashes on startup
Solution: Ensure you have write permissions in the directory

Problem: Account data lost after restart
Solution: Check if accounts.dat file exists in same directory as executable

Problem: Cannot compile
Solution: Ensure C++ compiler is installed and PATH is set correctly

Problem: "File cannot be opened" error
Solution: Check directory permissions and ensure no other program is using accounts.dat


Important Notes

- Keep your account number and PIN secure
- The accounts.dat file contains all your banking data
- Backup accounts.dat regularly to prevent data loss
- Do not edit accounts.dat manually
- Use only standard ASCII characters in names


Limitations

- Single-user system (no concurrent access)
- No transaction history or log
- No admin/user role separation
- No password recovery mechanism
- Basic console interface


Future Enhancements

- Multi-user support with customer and admin roles
- Transaction history and account statements
- Interest calculation for savings accounts
- Multiple account types (savings, checking)
- Fund transfer between accounts
- GUI interface
- Database integration


Educational Purpose

This project demonstrates:
- Object-Oriented Programming in C++
- File I/O operations and binary file handling
- Class design and encapsulation
- Data validation and error handling
- Menu-driven console applications


For more information or questions, refer to the source code comments in bank_management.cpp
