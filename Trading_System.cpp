#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account {
protected:
    double bitcoin_value = 20000;
    double crypto_invest = 0;
    double total_equity = 0;
    double balance = 0;
    double deposit = 0;
    double withdraw = 0;
    vector<pair<string, double>> transactions;

public:
    void Get_account_information() {
        total_equity = crypto_invest * bitcoin_value + balance;
        cout << "Bitcoin Value: " << bitcoin_value << endl;
        cout << "Crypto Invest: " << crypto_invest << endl;
        cout << "Total Equity: " << total_equity << endl;
        cout << "Balance: " << balance << endl;
    }

    bool Deposit(double amount) {
        if (amount < 0)
            return false;
        deposit += amount;
        balance += amount;
        transactions.push_back({ "Deposit:", amount });
        return true;
    }

    bool Withdraw(double amount) {
        if (amount > balance)
            return false;
        withdraw += amount;
        balance -= amount;
        transactions.push_back({ "Withdraw:", amount });
        return true;
    }

    virtual bool buy_crypto() = 0;
    virtual bool sell_crypto() = 0;
    void History() {
        cout << "Displaying All transactions\n";
        for (auto it : transactions) {
            cout << it.first << " " << it.second << endl;
        }

        char temp;
        cout << "Press any key to continue\n";
        cin >> temp;
    }
};

class User : public Account {
public:
    bool buy_crypto() override {
        cout << "Enter amount of Bitcoin to buy: ";
        double amount;
        cin >> amount;
        if (amount <= 0)
            return false;
        double total_amount = amount * bitcoin_value;
        if (total_amount > balance)
            return false;
        balance -= total_amount;
        crypto_invest += amount;
        total_equity = crypto_invest * bitcoin_value + balance;
        transactions.push_back({ "Buy Crypto:", amount });
        return true;
    }

    bool sell_crypto() override {
        cout << "Enter amount of Bitcoin to sell: ";
        double amount;
        cin >> amount;
        if (amount <= 0)
            return false;
        double total_amount = amount * bitcoin_value;
        crypto_invest -= amount;
        balance += total_amount;
        total_equity = crypto_invest * bitcoin_value + balance;
        transactions.push_back({ "Sell Crypto:", amount });
        return true;
    }
};

int main() {
    User person;
    char choice;
    double amount;
    bool check;

    while (true) {
        cout << "Press 1 if you want to Get your account information\n";
        cout << "Press 2 if you want to Deposit your money\n";
        cout << "Press 3 if you want to withdraw your money\n";
        cout << "Press 4 if you want to view your transaction history\n";
        cout << "Press 5 if you want to buy cryptocurrency\n";
        cout << "Press 6 if you want to sell cryptocurrency\n";
        cout << "Press any other key to exit\n";
        cout << " ******************************************\n";

        cin >> choice;

        switch (choice) {
        case '1':
            person.Get_account_information();
            break;

        case '2':
            cout << "Enter amount to deposit: ";
            cin >> amount;
            check = person.Deposit(amount);
            if (check == false)
                cout << "Insufficient Amount!\n";
            break;

        case '3':
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            check = person.Withdraw(amount);
            if (check == false)
                cout << "Insufficient Balance!\n";
            break;

        case '4':
            person.History();
            break;

        case '5':
            check = person.buy_crypto();
            if (check == true)
                cout << "Transaction Successfull.\n";
            if (check == false)
                cout << "Invalid amount!\n";
            break;

        case '6':
            check = person.sell_crypto();
             if (check == true)
                cout << "Transaction Successfull.\n";

            if (check == false)
                cout << "Invalid amount!\n";
            break;

        default:
            return 0;
        }
    }
}
