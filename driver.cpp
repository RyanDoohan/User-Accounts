#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

bool signed_in = false; // Global bool updated to true only if a user is signed into an account. False whenever the user is not signed in.
string current_signed_in_username = ""; // Global string to hold username, updated when the user succesfully signs into an account.

int print_welcome_message(); // Prints welcome menu selections returns users choice.
int print_signin_message(); // Prints signed-in menu selections returns users choice.
void create_account(); // Sets up new username and password and stores data into 'accounts_info.txt'.
void signin_account(); // Allows user to signin an existing account, parses 'accounts_info.txt' and validates password.
void print_current_users(); // Print a list of active current users in 'accounts_info.txt'.
int count_users(); // Returns the current number of users in 'accounts_info.txt'.
void signout_account(); // If the user is signed in, will sign the user out of their current account their signed into.
void delete_account(); // Deletes the account of a user who is signed in, will permanently delete the user from the system.

int main() {
    int users_choice_int; // int to hold which option the user selects from the main menu.

    users_choice_int = print_welcome_message(); // Print menu for the user, return which option they chose to users_choice_int.

    while(1) { // Loop until the user choses to exit the program.
        if(signed_in) {
            users_choice_int = print_signin_message(); // Call print_signin_message to display the signed-in menu. Return choice to users_choice_int.

            switch(users_choice_int) {
                case 1: {  // IF the user chose option 1 from the signed in menu,
                    create_account(); // Call create_account() function.
                    break;
                }
                case 2: {  // IF the user chose option 2 from the signed in menu,
                    print_current_users(); // Call print_current_users() function.
                    break;
                }
                case 3: {  // IF the user chose option 3 from the signed in menu,
                    delete_account(); // delete_account() function.
                    break;
                }
                case 4: {  // IF the user chose option 4 from the signed in menu,
                    signout_account(); // Call signout_account() function.
                    break;
                }
                case 5: {  // IF the user chose option 5 from the signed in menu,
                    abort(); // Exit the program.
                }
                break;
            } // End switch.
        }
        else {
            switch(users_choice_int) {
                case 1: { // IF the user chose option 1 from the welcome menu,
                    create_account(); // Call create_account() function.
                    break;
                }
                case 2: { // IF the user chose option 2 from the welcome menu,
                    signin_account(); // Call signin_account() function.
                    break;
                }
                case 3: { // IF the user chose option 3 from the welcome menu,
                    abort(); // Exit the program.
                }
                break;
            } // End switch.
            if(!signed_in) { // Only if the user is not signed in, we display the welcome menu.
                users_choice_int = print_welcome_message();  // Call print_welcome_message to display the signed-in menu. Return choice to users_choice_int.
            }
            
        }
    } // End while loop.

    return 0;
} // End main.

int print_welcome_message() {
    int list_menu_start = 1, list_menu_last = 3;
    string users_choice; // Holds which choice the user selects from the list.

    cout << "\n\nDemo Account Creation Software\n";
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
    int list_menu_start = 1, list_menu_last = 5; // list_menu_start and last hold the beginning and end values of the list.
    string users_choice; // Holds which choice the user selects from the list.

    cout << "\n\nDemo Account Creation Software\n";
    cout << "=-==============================-=\n\n";
    cout << "1.) Create a New Account\n";
    cout << "2.) List current users\n";
    cout << "3.) Delete Account\n";
    cout << "4.) Signout of Account\n";
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

    ofstream accountsInfoWrite ("accounts_info.txt", ios_base::app); // Write to 'accounts_info.txt'.
    ifstream accountsInfoRead ("accounts_info.txt"); // Read from 'accounts_info.txt'.

    cout << "\n\nCreate a New Account\n";
    cout << "=-==============================-=\n\n";
    cout << "Enter a Username here: ";

    getline(cin, username); // User input.

    cout << "Enter a Password here: ";

    getline(cin, password); // User input.

    cout << "\nA new account has been succesfully created with the following information\n";
    cout << "Username: " << username << endl;
    cout << "Password: " << password; // Display the account credentials the user created an account with.

    if(accountsInfoWrite.is_open()) { // Validate 'accounts_info.txt' opens correctly.
        accountsInfoWrite << newUserString << endl; // Write new iser identifier to 'accounts_info.txt' first.
        accountsInfoWrite << "#" << count_users() << endl; // Write the user # in 'accounts_info.txt'.
        accountsInfoWrite << username << endl; // Write the username to 'accounts_info.txt'.
        accountsInfoWrite << password << "\n\n"; // Write the password to 'accounts_info.txt'.
        accountsInfoWrite.close(); // Close the open 'accounts_info.txt' file.
    }
    else cout << "There was an error opening 'accounts_info.txt'. Please ensure this file exists and then restart the program.\n"; // Provide input validation feedback.
}

void signin_account() {
    string username, password, readFromFile; // username, stores inputted username. password, stores inoutted password. readFromFile, temp string to read file.

    ifstream accountsInfoRead ("accounts_info.txt"); // Read from 'accounts_info.txt'.

    cout << "\n\nSign-in to an existing account\n";
    cout << "=-==============================-=\n\n";
    cout << "Enter Username: ";

    getline(cin, username); // User input.

    while(username.compare("1") != 0) { // If the user wants to exit the signin menu, they may enter '1' to do so.
        while(accountsInfoRead >> readFromFile) { // Read through the entire 'accounts_info.txt' file.
            if(readFromFile.compare(username) == 0) { // Check if the entered username exists within 'accounts_info.txt'.
                cout << "Enter Password: ";
                getline(cin, password); // User input.
                accountsInfoRead >> readFromFile; // Read the next line of the file where the password exists.
                while(readFromFile.compare(password) != 0) { // Check if the password entered matches with the password in 'accounts_info.txt'.
                        cout << "Password entered was incorrect.\n";
                        cout << "Enter password here: ";
                            // IF the password does not match, user input for another password so the user can re-attempt the login.
                        getline(cin, password); // IF the user choses to leave the log-in prompt, they may enter '1'.
                }
                signed_in = true; // IF the user succesfully signs in, set global 'signed_in' bool to true.
                current_signed_in_username = username; // IF the user succesfully signs in set global 'current_signed_in_username'.
                cout << "\nSuccesfully signed into account!\n";
                return;
            }
        }

        cout << "User was not found!\n";
        cout << "To create a new account enter '1'.\n";
        cout << "Enter Username: "; // Prompt the user to enter another username.

        accountsInfoRead.clear(); // In case of reading past EOF, clear ifsteam buffer.
        accountsInfoRead.seekg(0); // We've gone through the entire file already, so seek back to the beginning of the file to look for another username.
            // User input.
        getline(cin, username);  // IF the user choses to leave the log-in prompt, they may enter '1'.
    }
    return;
}

void print_current_users() {
    string readFromFile, newUserString = "=User="; // readFromFile temp string to read file. newUserString, holds the identifier for a new user.

    ifstream accountsInfoRead ("accounts_info.txt"); // Read from 'accounts_info.txt'.

    cout << "\n\nNumber of current users in the system: " << count_users() << "\n"; // Display the # of users currently in 'accounts_info.txt'.
    cout << "=-====================================-=\n";

    while(accountsInfoRead >> readFromFile) { // Read through the entire 'accounts_info.txt' file.
        if(readFromFile.compare(newUserString) != 0) { // Check if the line we're on in 'accounts_info.txt' is a newUserString indentifier.
            if(readFromFile[0] != '#') { // Check we don't display the users number.
             cout << readFromFile; // Display each username in the 'accounts_info.txt' file.
             accountsInfoRead >> readFromFile; // Read the next line right away as it contains the password.
            }
        }
        else cout << "\n";
    }
}

int count_users() {
    int num_users = 0; // Initialize 'num_users' = 0 to count the users in the 'accounts_info.txt' file.

    string readFromFile, newUserString = "=User="; // readFromFile temp string to read file. newUserString, holds the identifier for a new user.
    ifstream accountsInfoRead ("accounts_info.txt"); // Read from 'accounts_info.txt'.

    while(accountsInfoRead >> readFromFile) { // Read through the entire 'accounts_info.txt' file.
        if(readFromFile.compare(newUserString) == 0) { // Check for everytime we come across a new user indentifier.
            num_users++; // Increment num_users by 1 each time we find a user in 'accounts_info.txt'.
        }
    }
    return num_users; // Return final count stored in num_users.
}

void signout_account() {
    string choice; // String choice, holds the user inputted choice to signout or not.

    if(signed_in) { // Check to make sure the user is actually signed into an account.
        cout << current_signed_in_username << ", are you sure you want to sign-out of your account?\n";
        cout << "(Y = yes / N = no)\n";
        cout << "Enter here: "; // Confirm the user actually wants to sign out of their account.

        getline(cin, choice); // User input.

        while(1) { // Loop until the user says no, or they succesfully sign out.
            if(choice == "Y" || choice == "y") {
                signed_in = false; // IF the user choses to sign out, update global 'signed_in' bool to false.
                current_signed_in_username = ""; // IF the user choses to sign out, update global 'current_signed_in_username' to "".
                cout << "\nSuccesfully signed out of your account!\n"; // Confirmation for the user.
                break;
            }
            else if(choice == "N" || choice == "n") { // IF the user choses not to sign out of their account.
                cout << "Returning to main menu...\n";
                break;
            }
            else {
                cout << "Invalid input! Acceptable inputs are ('Y' = yes / 'N' = no)\n";
                cout << "Enter here: "; // Input validation for (Y, y, N, n).

                getline(cin, choice); // User input.
            }
        }
    }
}

void delete_account() {
    
}