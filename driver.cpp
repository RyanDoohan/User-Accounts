#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int print_welcome_message();
void create_account();

int main() {
    int users_choice_int;

    users_choice_int = print_welcome_message();

    switch(users_choice_int) {
        case 1: {
            create_account();
            break;
        }
        case 2: {
            break;
        }
        break;
    }

    return 0;
}

int print_welcome_message() {
    string users_choice;

    cout << "Demo Account Creation Software\n";
    cout << "=-==============================-=\n\n";
    cout << "1.) Create a New Account\n";
    cout << "2.) Sign-in to an Existing Account\n\n";
    cout << "Enter here: ";

    getline(cin, users_choice);

    while(users_choice != "1" && users_choice != "2") { // Input validation check
        cout << "You have entered an invalid input. Accepted inputs are '1' or '2'. Please enter only accepted inputs to proceed.\n";
        cout << "Enter here: ";
        
        getline(cin, users_choice);
    }

    int users_choice_int = stoi(users_choice);
    return users_choice_int;
}

void create_account() {
    string username, password, readFromFile, newUserString = "=User=";
    int num_users = 0;

    ofstream accountsInfoWrite ("accounts_info.txt", ios_base::app);
    ifstream accountsInfoRead ("accounts_info.txt");

    cout << "\n\nCreate a New Account\n";
    cout << "=-==============================-=\n\n";
    cout << "Enter a Username here: ";

    getline(cin, username);

    cout << "Enter a Password here: ";

    getline(cin, password);

    cout << "\nA new account has been succesfully created with the following information\n";
    cout << "Username: " << username << endl;
    cout << "Password: " << password;

    while(accountsInfoRead >> readFromFile) {
        if(readFromFile.compare(newUserString) == 0) {
            num_users++;
        }
    }

    if(accountsInfoWrite.is_open()) {
        accountsInfoWrite << newUserString << endl;
        accountsInfoWrite << "#" << num_users+1 << endl;
        accountsInfoWrite << username << endl;
        accountsInfoWrite << password << "\n\n";
        accountsInfoWrite.close();
    }
    else cout << "There was an error opening 'accounts_info.txt'. Please ensure this file exists and then restart the program.\n";
}