#include <iostream>
#include <string.h>

using namespace std;

void print_welcome_message(string &users_chc);
void create_account();

int main() {
    string users_choice;

    print_welcome_message(users_choice);



    return 0;
}

void print_welcome_message(string &users_chc) {
    cout << "Demo Account Creation Software\n";
    cout << "=-==============================-=\n\n";
    cout << "1.) Create a New Account\n";
    cout << "2.) Sign-in to an Existing Account\n\n";
    cout << "Enter here: ";

    getline(cin, users_chc);

    while(users_chc != "1" && users_chc != "2") { // Input validation check
        cout << "You have entered an invalid input. Accepted inputs are '1' or '2'. Please enter only accepted inputs to proceed.\n";
        cout << "Enter here: ";
        
        getline(cin, users_chc);
    }
}

void create_account() {
    cout << "Create a New Account\n";
    cout << "=-==============================-=\n\n";
}