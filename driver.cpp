#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

bool signed_in = false;

int print_welcome_message(); // Prints welcome menu selections returns users choice.
int print_signin_message(); // Prints signed-in menu selections returns users choice.
void create_account(); // Sets up new username and password and stores data into 'accounts_info.txt'.
void signin_account(); // Allows user to signin an existing account, parses 'accounts_info.txt' and validates password.
void print_current_users(); // Print a list of active current users in 'accounts_info.txt'.
int count_users(); // Returns the current number of users in 'accounts_info.txt'.
void delete_account(); // Deletes the account of a user who is signed in, will permanently delete the user from the system.

int main() {
    int users_choice_int; // int to hold which option the user selects from the main menu.

    users_choice_int = print_welcome_message(); // Print menu for the user, return which option they chose to users_choice_int.

    while(1) {
        if(signed_in) {
            users_choice_int = print_signin_message();

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
                case 4: {
                    //delete_account();
                }
                case 5: {
                    abort();
                }
                break;
            }

            
        }
        else {
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
                    abort();
                }
                break;
            }

            
        }
    }

    return 0;
}

int print_welcome_message() {
    int list_menu_start = 1, list_menu_last = 3;
    string users_choice; // Holds which choice the user selects from the list.

    cout << "Demo Account Creation Software\n";
    cout << "=-==============================-=\n\n";
    cout << "1.) Create a New Account\n";
    cout << "2.) Sign-in to an Existing Account\n";
    cout << "3.) Exit\n";
    cout << "Enter here: ";

    getline(cin, users_choice); // User input.
    int users_choice_int = stoi(users_choice); // Convert the users option from a string to an integer value.

    while(users_choice_int > list_menu_last || users_choice_int < list_menu_start) { // Input validation check.
        cout << "You have entered an invalid input. Accepted inputs are '1' through '3'. Please enter only accepted inputs to proceed.\n";
        cout << "Enter here: ";
        
        getline(cin, users_choice); // User input.
        users_choice_int = stoi(users_choice); // Convert the users option from a string to an integer value.
    }

    return users_choice_int;
}

int print_signin_message() {
    int list_menu_start = 1, list_menu_last = 5;
    string users_choice; // Holds which choice the user selects from the list.

    cout << "Demo Account Creation Software\n";
    cout << "=-==============================-=\n\n";
    cout << "1.) Create a New Account\n";
    cout << "2.) Sign-in to an Existing Account\n";
    cout << "3.) List current users\n";
    cout << "4.) Delete Account\n";
    cout << "5.) Exit\n";
    cout << "Enter here: ";

    getline(cin, users_choice); // User input.
    int users_choice_int = stoi(users_choice); // Convert the users option from a string to an integer value.

    while(users_choice_int > list_menu_last || users_choice_int < list_menu_start) { // Input validation check.
        cout << "You have entered an invalid input. Accepted inputs are '1' through '4'. Please enter only accepted inputs to proceed.\n";
        cout << "Enter here: ";
        
        getline(cin, users_choice); // User input.
        users_choice_int = stoi(users_choice); // Convert the users option from a string to an integer value.
    }

    return users_choice_int;
}

void create_account() {
    string username, password, // username holds the inputted username, passwords holds the inputted password.
    readFromFile, newUserString = "=User="; // readFromFile parses through the data file, newUserString holds the identifier for a new user.

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

    if(accountsInfoWrite.is_open()) {
        accountsInfoWrite << newUserString << endl;
        accountsInfoWrite << "#" << count_users() << endl;
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
                signed_in = true;
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
    cout << "\n\n";
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