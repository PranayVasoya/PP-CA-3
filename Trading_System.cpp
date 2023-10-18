#include <iostream>
#include <vector>
#include <iomanip> 
using namespace std;

class Account {
    int dogecoin, balance;
    int bitcoin;
    int deposit, withdraw;
    int total_equity = 100;
    int predict;
    int dogecoin_value;
    int bitcoin_value;
    int crypto_invest;
    int crypto_return;

    vector<pair<string, int>> transactions;

public:
    bool Deposit(int money) {
        deposit += money;
        balance += money;
        transactions.push_back({ "Deposit:", money });
        return true;
    }
    void Get_account_information() {
        cout << "Account Information:\n";
        cout << left << setw(20) << "Bank Balance:" << setw(10) << balance << endl;
        cout << left << setw(20) << "Dogecoin:" << setw(10) << dogecoin << endl;
        cout << left << setw(20) << "Bitcoin:" << setw(10) << bitcoin << endl;
    }
    bool Withdraw(int money) {
        if (money > balance) {
            return false;
        }

        withdraw += money;
        balance -= money;
        transactions.push_back({ "Withdraw:", money });
        return true;
    }

    bool buy_crypto() {
        int option;
        cout << "Want to purchase dogecoin press 1 else for bitcoin press 2\n";
        cin >> option;

        if (total_equity != 0) {
            if (option == 1 && balance >= dogecoin_value) {
                dogecoin += 1;
                balance -= dogecoin_value;
                crypto_invest += (dogecoin)*dogecoin_value;
            }
            else if (option == 2 && balance >= bitcoin_value) {
                bitcoin += 1;
                balance -= bitcoin_value;
                crypto_invest += bitcoin_value;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }

        return true;
    }

    bool sell_crypto() {
        int option;
        cout << "Want to sell dogecoin press 1 else for bitcoin press 2\n";
        cin >> option;

        if (option == 2) {
            if (bitcoin == 0)
                return false;
            crypto_return += bitcoin_value;
            balance += bitcoin_value;
            transactions.push_back({ "Bitcoin Sold:", bitcoin_value });
            bitcoin -= 1;
        }
        else {
            if (dogecoin == 0)
                return false;
            crypto_return += dogecoin_value;
            balance += dogecoin_value;
            transactions.push_back({ "Dogecoin Sold:", dogecoin_value });
            dogecoin -= 1;
        }

        return true;
    }
    void History() {
        cout << "Displaying All transactions\n";
        for (auto it : transactions) {
            cout << it.first << " " << it.second << endl;
        }

        char temp;
        cout << "Do you want to clear all transactions:";
        cin >> temp;

        int no = transactions.size();

        if (temp == 'Y') {
            transactions.clear();
            cout << "Total transactions cleared:" << no << endl;
        }
        else if(temp=='N'){
            cout << "Total transaction:" << no << endl;
        }
    }

    Account() {
        crypto_invest = 0;
        crypto_return = 0;
        total_equity = 100;
        balance = 50000;
        dogecoin = 0;
        bitcoin = 0;
        withdraw = 0;
        deposit = 0;
        dogecoin_value = 100;
        bitcoin_value = 500;
    }
};

int main() {
    Account person;
    int amount, choice;
    bool check;

    while (true) {
        cout << "  ******************************************\n";
        cout << "Press 1 if you want to view your Account Info\n";
        cout << "Press 2 if you want to Deposit your money\n";
        cout << "Press 3 if you want to withdraw your money\n";
        cout << "Press 4 if you want to view your transaction history\n";
        cout << "Press 5 if you want to buy cryptocurrency\n";
        cout << "Press 6 if you want to sell cryptocurrency\n";
        cout << "Press any other key to exit\n";
        cout << "  ******************************************\n";

        cin >> choice;

        switch (choice) {
        case 1:
            person.Get_account_information();
            break;

        case 2:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            check = person.Deposit(amount);
            if (check)
                cout << "Successfully deposited money\n";
            else
                cout << "Failed\n";
            break;

        case 3:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            check = person.Withdraw(amount);
            if (check)
                cout << "Successfully withdrawn Amount\n";
            else
                cout << "Not Enough Balance\n";
            break;

        case 4:
            person.History();
            break;

        case 5:
            check = person.buy_crypto();
            if (check)
                cout << "Successful Transaction\n";
            else
                cout << "Unable to make the purchase\n";
            break;

        case 6:
            check = person.sell_crypto();
            if (check)
                cout << "Successful Transaction\n";
            else
                cout << "Unable to make the sale\n";
            break;

        default:
            exit(0);
            break;
        }
    }

    return 0;
}