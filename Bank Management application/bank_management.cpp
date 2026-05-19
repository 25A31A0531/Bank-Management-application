#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Account Class - Core OOP Component
class Account {
private:
    int accountNumber;
    char name[50];
    double balance;
    char pin[5];  // 4-digit PIN
    
public:
    // Constructor
    Account() {
        accountNumber = 0;
        strcpy(name, "");
        balance = 0.0;
        strcpy(pin, "0000");
    }
    
    // Setters
    void setAccountNumber(int accNo) {
        accountNumber = accNo;
    }
    
    void setName(const char* n) {
        strncpy(name, n, 49);
        name[49] = '\0';
    }
    
    void setBalance(double bal) {
        balance = bal;
    }
    
    void setPIN(const char* p) {
        strncpy(pin, p, 4);
        pin[4] = '\0';
    }
    
    // Getters
    int getAccountNumber() const {
        return accountNumber;
    }
    
    const char* getName() const {
        return name;
    }
    
    double getBalance() const {
        return balance;
    }
    
    bool verifyPIN(const char* p) const {
        return strcmp(pin, p) == 0;
    }
    
    // Banking Operations
    bool deposit(double amount) {
        if (amount <= 0) {
            cout << "\n\tInvalid amount! Deposit failed." << endl;
            return false;
        }
        balance += amount;
        cout << "\n\t$" << fixed << setprecision(2) << amount 
             << " deposited successfully!" << endl;
        return true;
    }
    
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "\n\tInvalid amount! Withdrawal failed." << endl;
            return false;
        }
        if (amount > balance) {
            cout << "\n\tInsufficient balance! Withdrawal failed." << endl;
            return false;
        }
        balance -= amount;
        cout << "\n\t$" << fixed << setprecision(2) << amount 
             << " withdrawn successfully!" << endl;
        return true;
    }
    
    void displayAccount() const {
        cout << "\n\t" << string(50, '=') << endl;
        cout << "\t  ACCOUNT DETAILS" << endl;
        cout << "\t" << string(50, '=') << endl;
        cout << "\tAccount Number : " << accountNumber << endl;
        cout << "\tAccount Holder : " << name << endl;
        cout << "\tCurrent Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "\t" << string(50, '=') << endl;
    }
    
    void displayBalanceOnly() const {
        cout << "\n\tCurrent Balance: $" << fixed << setprecision(2) << balance << endl;
    }
};

// Bank Management System Class
class BankSystem {
private:
    const char* filename = "accounts.dat";
    
    void drawHeader(const char* title) {
        cout << "\n\n";
        cout << "\t" << string(60, '*') << endl;
        cout << "\t*" << string(58, ' ') << "*" << endl;
        cout << "\t*" << setw(40) << title << string(18, ' ') << "*" << endl;
        cout << "\t*" << string(58, ' ') << "*" << endl;
        cout << "\t" << string(60, '*') << endl;
    }
    
    int generateAccountNumber() {
        ifstream inFile(filename, ios::binary);
        if (!inFile) {
            return 1001; // First account number
        }
        
        int lastAccNo = 1000;
        Account acc;
        while (inFile.read((char*)&acc, sizeof(Account))) {
            if (acc.getAccountNumber() > lastAccNo) {
                lastAccNo = acc.getAccountNumber();
            }
        }
        inFile.close();
        return lastAccNo + 1;
    }
    
    bool accountExists(int accNo) {
        ifstream inFile(filename, ios::binary);
        if (!inFile) return false;
        
        Account acc;
        while (inFile.read((char*)&acc, sizeof(Account))) {
            if (acc.getAccountNumber() == accNo) {
                inFile.close();
                return true;
            }
        }
        inFile.close();
        return false;
    }
    
    bool readAccount(int accNo, Account& acc) {
        ifstream inFile(filename, ios::binary);
        if (!inFile) return false;
        
        while (inFile.read((char*)&acc, sizeof(Account))) {
            if (acc.getAccountNumber() == accNo) {
                inFile.close();
                return true;
            }
        }
        inFile.close();
        return false;
    }
    
    void updateAccount(const Account& acc) {
        fstream file(filename, ios::binary | ios::in | ios::out);
        if (!file) {
            cout << "\n\tError: Unable to open file!" << endl;
            return;
        }
        
        Account tempAcc;
        while (file.read((char*)&tempAcc, sizeof(Account))) {
            if (tempAcc.getAccountNumber() == acc.getAccountNumber()) {
                int pos = -1 * static_cast<int>(sizeof(Account));
                file.seekp(pos, ios::cur);
                file.write((char*)&acc, sizeof(Account));
                break;
            }
        }
        file.close();
    }
    
public:
    void createAccount() {
        drawHeader("CREATE NEW ACCOUNT");
        
        Account acc;
        char name[50], pin[5];
        double initialDeposit;
        
        int accNo = generateAccountNumber();
        acc.setAccountNumber(accNo);
        
        cout << "\n\tEnter Account Holder Name: ";
        cin.ignore();
        cin.getline(name, 50);
        acc.setName(name);
        
        cout << "\tSet 4-Digit PIN: ";
        cin >> pin;
        while (strlen(pin) != 4) {
            cout << "\tPIN must be exactly 4 digits! Try again: ";
            cin >> pin;
        }
        acc.setPIN(pin);
        
        cout << "\tEnter Initial Deposit ($): ";
        cin >> initialDeposit;
        while (initialDeposit < 0) {
            cout << "\tInvalid amount! Enter again: ";
            cin >> initialDeposit;
        }
        acc.setBalance(initialDeposit);
        
        // Save to file
        ofstream outFile(filename, ios::binary | ios::app);
        outFile.write((char*)&acc, sizeof(Account));
        outFile.close();
        
        cout << "\n\t" << string(50, '=') << endl;
        cout << "\tAccount Created Successfully!" << endl;
        cout << "\tYour Account Number is: " << accNo << endl;
        cout << "\t(Please remember this number for future transactions)" << endl;
        cout << "\t" << string(50, '=') << endl;
    }
    
    void depositMoney() {
        drawHeader("DEPOSIT MONEY");
        
        int accNo;
        char pin[5];
        
        cout << "\n\tEnter Account Number: ";
        cin >> accNo;
        
        if (!accountExists(accNo)) {
            cout << "\n\tAccount not found!" << endl;
            return;
        }
        
        Account acc;
        readAccount(accNo, acc);
        
        cout << "\tEnter PIN: ";
        cin >> pin;
        
        if (!acc.verifyPIN(pin)) {
            cout << "\n\tIncorrect PIN! Transaction cancelled." << endl;
            return;
        }
        
        double amount;
        cout << "\tEnter Amount to Deposit ($): ";
        cin >> amount;
        
        if (acc.deposit(amount)) {
            updateAccount(acc);
            acc.displayBalanceOnly();
        }
    }
    
    void withdrawMoney() {
        drawHeader("WITHDRAW MONEY");
        
        int accNo;
        char pin[5];
        
        cout << "\n\tEnter Account Number: ";
        cin >> accNo;
        
        if (!accountExists(accNo)) {
            cout << "\n\tAccount not found!" << endl;
            return;
        }
        
        Account acc;
        readAccount(accNo, acc);
        
        cout << "\tEnter PIN: ";
        cin >> pin;
        
        if (!acc.verifyPIN(pin)) {
            cout << "\n\tIncorrect PIN! Transaction cancelled." << endl;
            return;
        }
        
        double amount;
        cout << "\tEnter Amount to Withdraw ($): ";
        cin >> amount;
        
        if (acc.withdraw(amount)) {
            updateAccount(acc);
            acc.displayBalanceOnly();
        }
    }
    
    void checkBalance() {
        drawHeader("BALANCE INQUIRY");
        
        int accNo;
        char pin[5];
        
        cout << "\n\tEnter Account Number: ";
        cin >> accNo;
        
        if (!accountExists(accNo)) {
            cout << "\n\tAccount not found!" << endl;
            return;
        }
        
        Account acc;
        readAccount(accNo, acc);
        
        cout << "\tEnter PIN: ";
        cin >> pin;
        
        if (!acc.verifyPIN(pin)) {
            cout << "\n\tIncorrect PIN! Access denied." << endl;
            return;
        }
        
        acc.displayAccount();
    }
    
    void displayAllAccounts() {
        drawHeader("ALL ACCOUNTS");
        
        ifstream inFile(filename, ios::binary);
        if (!inFile) {
            cout << "\n\tNo accounts found!" << endl;
            return;
        }
        
        Account acc;
        bool found = false;
        
        cout << "\n\t" << string(70, '-') << endl;
        cout << "\t" << setw(10) << "Acc No" 
             << setw(30) << "Name" 
             << setw(15) << "Balance" << endl;
        cout << "\t" << string(70, '-') << endl;
        
        while (inFile.read((char*)&acc, sizeof(Account))) {
            cout << "\t" << setw(10) << acc.getAccountNumber()
                 << setw(30) << acc.getName()
                 << "  $" << setw(12) << fixed << setprecision(2) 
                 << acc.getBalance() << endl;
            found = true;
        }
        
        if (!found) {
            cout << "\t" << setw(35) << "No accounts found!" << endl;
        }
        
        cout << "\t" << string(70, '-') << endl;
        inFile.close();
    }
    
    void modifyAccount() {
        drawHeader("MODIFY ACCOUNT");
        
        int accNo;
        char pin[5];
        
        cout << "\n\tEnter Account Number: ";
        cin >> accNo;
        
        if (!accountExists(accNo)) {
            cout << "\n\tAccount not found!" << endl;
            return;
        }
        
        Account acc;
        readAccount(accNo, acc);
        
        cout << "\tEnter PIN: ";
        cin >> pin;
        
        if (!acc.verifyPIN(pin)) {
            cout << "\n\tIncorrect PIN! Access denied." << endl;
            return;
        }
        
        cout << "\n\tCurrent Account Details:" << endl;
        acc.displayAccount();
        
        char name[50];
        cout << "\n\tEnter New Name (or press Enter to keep current): ";
        cin.ignore();
        cin.getline(name, 50);
        if (strlen(name) > 0) {
            acc.setName(name);
        }
        
        char newPin[5];
        cout << "\tEnter New PIN (or 0000 to keep current): ";
        cin >> newPin;
        if (strcmp(newPin, "0000") != 0 && strlen(newPin) == 4) {
            acc.setPIN(newPin);
            cout << "\tPIN updated successfully!" << endl;
        }
        
        updateAccount(acc);
        cout << "\n\tAccount modified successfully!" << endl;
    }
    
    void deleteAccount() {
        drawHeader("DELETE ACCOUNT");
        
        int accNo;
        char pin[5];
        
        cout << "\n\tEnter Account Number: ";
        cin >> accNo;
        
        if (!accountExists(accNo)) {
            cout << "\n\tAccount not found!" << endl;
            return;
        }
        
        Account acc;
        readAccount(accNo, acc);
        
        cout << "\tEnter PIN: ";
        cin >> pin;
        
        if (!acc.verifyPIN(pin)) {
            cout << "\n\tIncorrect PIN! Access denied." << endl;
            return;
        }
        
        char confirm;
        cout << "\n\tAre you sure you want to delete this account? (Y/N): ";
        cin >> confirm;
        
        if (confirm != 'Y' && confirm != 'y') {
            cout << "\n\tDeletion cancelled." << endl;
            return;
        }
        
        // Create temporary file
        ifstream inFile(filename, ios::binary);
        ofstream outFile("temp.dat", ios::binary);
        
        Account tempAcc;
        while (inFile.read((char*)&tempAcc, sizeof(Account))) {
            if (tempAcc.getAccountNumber() != accNo) {
                outFile.write((char*)&tempAcc, sizeof(Account));
            }
        }
        
        inFile.close();
        outFile.close();
        
        remove(filename);
        rename("temp.dat", filename);
        
        cout << "\n\tAccount deleted successfully!" << endl;
    }
};

// Main Menu
void displayMainMenu() {
    cout << "\n\n";
    cout << "\t" << string(60, '=') << endl;
    cout << "\t    BANK MANAGEMENT SYSTEM - MAIN MENU" << endl;
    cout << "\t" << string(60, '=') << endl;
    cout << "\t    1. Create New Account" << endl;
    cout << "\t    2. Deposit Money" << endl;
    cout << "\t    3. Withdraw Money" << endl;
    cout << "\t    4. Check Balance" << endl;
    cout << "\t    5. Display All Accounts" << endl;
    cout << "\t    6. Modify Account" << endl;
    cout << "\t    7. Delete Account" << endl;
    cout << "\t    8. Exit" << endl;
    cout << "\t" << string(60, '=') << endl;
    cout << "\t    Enter your choice: ";
}

int main() {
    BankSystem bank;
    int choice;
    
    cout << "\n\n";
    cout << "\t" << string(60, '*') << endl;
    cout << "\t*" << string(58, ' ') << "*" << endl;
    cout << "\t*" << setw(45) << "WELCOME TO BANK MANAGEMENT SYSTEM" 
         << string(13, ' ') << "*" << endl;
    cout << "\t*" << string(58, ' ') << "*" << endl;
    cout << "\t" << string(60, '*') << endl;
    
    do {
        displayMainMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.depositMoney();
                break;
            case 3:
                bank.withdrawMoney();
                break;
            case 4:
                bank.checkBalance();
                break;
            case 5:
                bank.displayAllAccounts();
                break;
            case 6:
                bank.modifyAccount();
                break;
            case 7:
                bank.deleteAccount();
                break;
            case 8:
                cout << "\n\t" << string(60, '=') << endl;
                cout << "\t    Thank you for using Bank Management System!" << endl;
                cout << "\t" << string(60, '=') << endl;
                break;
            default:
                cout << "\n\tInvalid choice! Please try again." << endl;
        }
        
        if (choice != 8) {
            cout << "\n\tPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
        
    } while(choice != 8);
    
    return 0;
}
