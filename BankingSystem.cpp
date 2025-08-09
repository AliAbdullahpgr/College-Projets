
#include <iostream>
#include <string>
#include<fstream>
#include<iomanip>
#include <vector>
#include<conio.h>
using namespace std;
//This is a project of my 2nd semester OOP
class Account {
private:
    int account_no;
    string accName;
    string accPin;
    double accBal;
    string accMotherName;
    bool accountType;
public:
    Account(string name,string motherName, string& password,bool accountType) : accName(name),accMotherName(motherName) ,accPin(password), accBal(0),accountType(accountType) {}
    bool validatePassword(const string& password)const{
        return (password == accPin);
    }
    bool validateCredentials(const string& name,const string& motherName) const {
        return (name == accName &&motherName==accMotherName);
    }

    double getBalance() const {
        return accBal;
    }
    bool getAccountType(){
        return accountType;
    }
    void deposit(double amount) {
        if (accountType) {
            if(amount<=50000 && amount>0){
            accBal += amount;
            }else{
            cout << "Invalid deposit amount." << endl;
            }
        } else if(!accountType){
            if(amount<=100000 && amount>0){
            accBal += amount;
            } 
            else{
            cout << "Invalid deposit amount." << endl;
        }
        }else{
            cout<<"Invalid Input."<<endl;
        }
    }

    bool withdraw(double amount) {
        if (accountType) {
            if(amount<=50000 && amount>0&& amount<accBal){
            accBal -= amount;
            return true;
            }else{
            cout << "Invalid or insufficient amount for withdrawal." << endl;
            return false;
            }
        } else if(!accountType){
            if(amount<=100000 && amount>0){
            accBal += amount;
            } else {
            cout << "Invalid or insufficient amount for withdrawal." << endl;
            return false;
            }
            }else{
            cout<<"Invalid Input."<<endl;
            return false;
        }

    }

    string getName() const {
        return accName;
    }

    void setName(const string& newName) {
        accName = newName;
    }

    void setPin(const string& newPin) {
    accPin = newPin; 
}

};

class Bank {
private:
    vector<Account> accounts;
public:
    void signUp() {
        string name,motherName;
        string password;
        int i = 0;
        char ch;
        bool Savings = true;
        char type;
        cout << "Enter Account Name: ";
        cin.ignore();
        getline(cin, name);
        cout<< "Enter Mother Name: ";
        getline(cin,motherName);
        cout << "Enter Pin Number: ";
        while (true) {
        ch = _getch();
        if (ch == 13){
        break;
        }
        password.push_back(ch);
        cout << "*";
        i++; 
        password[i] = '\0';
    }
        cout<<"\nWhich type of Account You want (C/S)\n>=50000 for Saving and >=100000 for current: "<<endl;
        cin>>type;
        type = toupper(type);
        if(type=='C'){
            Savings = false;
        }else if(type=='S'){
            Savings = true;
        }
        cout<<"Your Password is "<<password<<" Remember it\n";
        accounts.push_back(Account(name,motherName,password,Savings));
        cout << "New Account Successfully Created\n";
    }

Account* login() {
    string name, motherName;
    string password;
    bool flag = false;
    int attempts = 0;
    

    while (!flag && attempts < 3) {
        password.clear(); 
        char ch;
        cout << "\nEnter Account Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Mother Name: ";
        getline(cin, motherName);
        cout << "\nEnter Password (Attempt " << attempts + 1 << "/3): ";
            while (true) {
            ch = _getch();
            if (ch == 13) 
                break;
            password.push_back(ch);
            cout << "*"; 
        }
        
        for (auto& acc : accounts) {
            if(acc.validatePassword(password) && acc.validateCredentials(name, motherName)){
                flag = true;
                cout << "Login Successful\n";
                return &acc;
            }
        }
        cout << "\nInvalid Credentials. Please try again." << endl;
        attempts++; 
    }
    
    if (attempts >= 3) {
        cout << "Maximum password attempts reached. Exiting...\n";
        exit(0);
    }
    
    cout << "Maximum password attempts reached. Exiting...\n";
    return nullptr;
}



    void accountMenu(Account* acc) {
    while (true) {
        int choice;
        cout << "Welcome to our Bank, " << acc->getName() << endl;
        cout << "=============================================\n";
        cout << "[1] Deposit\n";
        cout << "[2] Withdraw\n";
        cout << "[3] Show Account Balance\n";
        cout << "[4] Edit Account\n";
        cout << "[5] Logout\n";
        cout << "[6] Transaction History\n";
        cout << "Input: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            double amount;
            cout << "Enter the amount to be deposited: ";
            cin >> amount;
            ofstream outputFile("transaction_history.txt", ios::app);
            if (outputFile.is_open()) {
                outputFile << __DATE__ << " " << __TIME__ << " $" << fixed << setprecision(2) << amount << " Deposited from "<<acc->getName() << endl;
                outputFile.close();
            } else {
                cout << "Error opening the file." << endl;
            }
            acc->deposit(amount);
            break;
        }
        case 2: {
            double amount;
            cout << "Enter the amount to be withdrawn: ";
            cin >> amount;
            ofstream outputFile("transaction_history.txt", ios::app);
            if (outputFile.is_open()) {
                outputFile << __DATE__ << " " << __TIME__ << " $" << fixed << setprecision(2) << amount << " Withdrawn from " << acc->getName()<< endl;
                outputFile.close();
            } else {
                cout << "Error opening the file." << endl;
            }
            acc->withdraw(amount);
            break;
        }
        case 3:
            cout << "Name: " << acc->getName() << endl;
            cout << "Balance: " << acc->getBalance() << "$" << endl;
            break;
        case 4:
            editAccount(acc);
            break;
        case 5:
            return;
        case 6: {
            ifstream fin("transaction_history.txt");
            if (!fin) {
                cout << "Error opening transaction history file." << endl;
                break;
            }
            string line;
            while (getline(fin, line)) {
                cout << line << endl;
            }
            fin.close();
            break;
        }
        default:
            cout << "Invalid Input\n";
            break;
        }
    }
}


    void editAccount(Account* acc) {
        int choice;
        cout << "[1] Change Account Name\n";
        cout << "[2] Change Pin Number\n";
        cout << "Input: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string newName;
            cout << "Enter New Account Name: ";
            getline(cin, newName);
            acc->setName(newName);
            cout << "Account Name Changed Successfully\n";
            break;
        }
        case 2: {
            string newPin;
            cout << "Enter New Pin Number: ";
            cin >> newPin;
            acc->setPin(newPin);
            cout << "Pin Changed Successfully\n";
            break;
        }
        default:
            cout << "Invalid Input\n";
            break;
        }
    }

    void bankMenu() {
        while (true) {
            int choice;
            cout << "=============================================\n";
            cout << "[1] Sign up\n";
            cout << "[2] Login\n";
            cout << "[3] Exit\n";
            cout << "Input: ";
            cin >> choice;

            switch (choice) {
            case 1:
                signUp();
                break;
            case 2: {
                Account* acc = login();
                if (acc) {
                    accountMenu(acc);
                }
                break;
            }
            case 3:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid Input\n";
                break;
            }
        }
    }
};

int main() {
    Bank bank;
    bank.bankMenu();
    return 0;
}