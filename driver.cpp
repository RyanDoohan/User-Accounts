#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

int print_welcome_message();
void create_account();
void signin_account();
void print_current_users();
int count_users();

int main() {
    int users_choice_int;

    users_choice_int = print_welcome_message();

    switch(users_choice_int) {
        case 1: {
            create_account();
            break;
        }
        case 2: {
            signin_account();
            break;
        }
        case 3: {
            print_current_users();
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
    cout << "2.) Sign-in to an Existing Account\n";
    cout << "3.) List current users\n";
    cout << "Enter here: ";

    getline(cin, users_choice);

    while(users_choice != "1" && users_choice != "2" && users_choice != "3") { // Input validation check
        cout << "You have entered an invalid input. Accepted inputs are '1' or '2' or '3'. Please enter only accepted inputs to proceed.\n";
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

void signin_account() {
    string username, password, readFromFile;

    ifstream accountsInfoRead ("accounts_info.txt");

    cout << "\n\nSign-in to an existing account\n";
    cout << "=-==============================-=\n\n";
    cout << "Enter Username: ";

    getline(cin, username);

    while(username.compare("1") != 0) {
        while(accountsInfoRead >> readFromFile) {
            if(readFromFile.compare(username) == 0) {
                cout << "Enter Password: ";
                getline(cin, password);
                accountsInfoRead >> readFromFile;
                while(readFromFile.compare(password) != 0) {
                        cout << "Password entered was incorrect.\n";
                        cout << "Enter password here: ";

                        getline(cin, password);
                }
                cout << "Succesfully signed into account!\n";
                return;
            }
        }

        cout << "User was not found!\n";
        cout << "To create a new account enter '1'.\n";
        cout << "Enter Username: ";

        accountsInfoRead.clear();
        accountsInfoRead.seekg(0);

        getline(cin, username);
    }

}

void print_current_users() {
    string readFromFile, newUserString = "=User=";
    ifstream accountsInfoRead ("accounts_info.txt");

    cout << "\n\nNumber of current users in the system: " << count_users() << "\n";
    cout << "=-====================================-=\n";

    while(accountsInfoRead >> readFromFile) {
        if(readFromFile.compare(newUserString) != 0) {
            if(readFromFile[0] != '#') {
             cout << readFromFile;
             accountsInfoRead >> readFromFile;
            }
        }
        else cout << "\n";
    }
}

int count_users() {
    int num_users = 0;

    string readFromFile, newUserString = "=User=";
    ifstream accountsInfoRead ("accounts_info.txt");

    while(accountsInfoRead >> readFromFile) {
        if(readFromFile.compare(newUserString) == 0) {
            num_users++;
        }
    }
    return num_users;
}