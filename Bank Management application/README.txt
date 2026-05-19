BANK MANAGEMENT SYSTEM - C++ APPLICATION
=========================================

OVERVIEW
--------
A complete banking application built with C++ that demonstrates object-oriented
programming principles and file handling for persistent data storage.

KEY FEATURES
------------
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
   - Transaction history maintained

OBJECT-ORIENTED DESIGN
----------------------
1. Account Class
   - Encapsulates account data (account number, name, balance, PIN)
   - Methods: deposit(), withdraw(), displayAccount(), verifyPIN()
   - Private data members with public getter/setter methods

2. BankSystem Class
   - Manages all banking operations
   - File I/O operations
   - Account CRUD operations (Create, Read, Update, Delete)

COMPILATION INSTRUCTIONS
------------------------

For Windows (MinGW/GCC):
   g++ bank_management.cpp -o bank_management.exe
   bank_management.exe

For Windows (MSVC):
   cl bank_management.cpp
   bank_management.exe

For Linux/Mac:
   g++ bank_management.cpp -o bank_management
   ./bank_management

USAGE GUIDE
-----------

1. CREATE NEW ACCOUNT
   - Select option 1 from main menu
   - Enter account holder name
   - Set a 4-digit PIN (remember this!)
   - Enter initial deposit amount
   - System generates unique account number automatically
   - Note down your account number for future use

2. DEPOSIT MONEY
   - Select option 2
   - Enter your account number
   - Enter your 4-digit PIN
   - Enter deposit amount
   - Confirmation and new balance displayed

3. WITHDRAW MONEY
   - Select option 3
   - Enter your account number
   - Enter your 4-digit PIN
   - Enter withdrawal amount
   - System checks for sufficient balance
   - Confirmation and new balance displayed

4. CHECK BALANCE
   - Select option 4
   - Enter your account number
   - Enter your 4-digit PIN
   - Complete account details displayed

5. VIEW ALL ACCOUNTS
   - Select option 5
   - Displays list of all accounts with balances
   - No PIN required (admin view)

6. MODIFY ACCOUNT
   - Select option 6
   - Enter your account number
   - Enter your 4-digit PIN
   - Update name and/or PIN

7. DELETE ACCOUNT
   - Select option 7
   - Enter your account number
   - Enter your 4-digit PIN
   - Confirm deletion
   - Account permanently removed

TECHNICAL SPECIFICATIONS
------------------------
- Language: C++ (Standard C++11 or higher)
- File Format: Binary (.dat)
- Storage File: accounts.dat (created automatically)
- Character Encoding: ASCII only (no Unicode)
- Account Number: Auto-incremented starting from 1001
- PIN Length: Exactly 4 digits
- Currency: Dollar ($) with 2 decimal places

FILE STRUCTURE
--------------
The application uses binary file handling for secure data storage:

accounts.dat
   - Binary file storing Account objects
   - Each record is sizeof(Account) bytes
   - Fields: accountNumber, name, balance, pin
   - Created automatically on first account creation

SECURITY FEATURES
-----------------
1. PIN Authentication
   - All transactions require PIN verification
   - 4-digit numeric PIN
   - Stored securely in binary format

2. Input Validation
   - Negative amounts rejected
   - Insufficient balance checks
   - PIN length validation
   - Account existence verification

3. Data Integrity
   - Binary file format prevents casual tampering
   - Atomic file operations
   - Confirmation for destructive operations

ERROR HANDLING
--------------
- Invalid account numbers detected
- Incorrect PIN attempts blocked
- Insufficient balance warnings
- Invalid amount checks
- File operation error handling

SAMPLE WORKFLOW
---------------
1. Start the application
2. Create account: "John Doe", PIN: 1234, Deposit: $1000
   -> Account number 1001 created
3. Deposit $500 to account 1001
   -> New balance: $1500
4. Withdraw $300 from account 1001
   -> New balance: $1200
5. Check balance
   -> Shows $1200
6. Exit

TESTING CHECKLIST
-----------------
[ ] Create multiple accounts
[ ] Deposit different amounts
[ ] Withdraw with sufficient balance
[ ] Try to withdraw more than balance (should fail)
[ ] Enter wrong PIN (should deny access)
[ ] Check balance displays correctly
[ ] Modify account name
[ ] Change PIN
[ ] Delete account with confirmation
[ ] View all accounts list
[ ] Exit and restart (data should persist)

LIMITATIONS
-----------
- Single-user system (no concurrent access)
- No transaction history/log
- No admin/user role separation
- No password recovery mechanism
- No account statements
- Basic console interface

FUTURE ENHANCEMENTS
-------------------
- Multi-user support with separate customer/admin roles
- Transaction history and statements
- Interest calculation
- Account types (savings, checking)
- Fund transfer between accounts
- Password recovery system
- GUI interface
- Database integration
- Network support for remote banking

TROUBLESHOOTING
---------------
Q: Program crashes on startup
A: Ensure you have write permissions in the directory

Q: Account data lost after restart
A: Check if accounts.dat file exists in same directory as executable

Q: Cannot compile
A: Ensure C++ compiler is installed and PATH is set correctly

Q: "File cannot be opened" error
A: Check directory permissions and ensure no other program is using accounts.dat

NOTES
-----
- Keep your account number and PIN secure
- The accounts.dat file contains all your banking data
- Backup accounts.dat regularly to prevent data loss
- Do not edit accounts.dat manually
- ASCII only - no special characters in names

SUPPORT
-------
This is an educational project demonstrating:
- Object-Oriented Programming in C++
- File I/O operations
- Class design and encapsulation
- Data validation and error handling
- Menu-driven console applications

For questions or issues, refer to the source code comments.
