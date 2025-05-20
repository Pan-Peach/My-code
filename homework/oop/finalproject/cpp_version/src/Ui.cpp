#include <iostream>
#include "../include/Ui.h"
#include "../include/System.h"

using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#elif __linux__
    #define CLEAR "clear"
#elif __APPLE__
    // macOS 平台代码
#else
    // 其他平台
#endif

void Ui::pause() {
    cout << "Press Enter to continue..." << endl;
    cin.ignore();
    cin.get();
}

void Ui::clearScreen() {
    system(CLEAR);
}

void Ui::displayMainMenu() {
    clearScreen();
    cout << "Welcome to the Package Management System!" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select an option: ";
    string choice;
    cin >> choice;
    clearScreen();
    if (choice == "1") {
        displayLoginMenu();
    } else if (choice == "2") {
        displayRegisterMenu();
    } else if (choice == "3") {
        cout << "Exiting the system. Goodbye!" << endl;
        pause();
        System::getInstance()->exitSys();
    } else {
        cout << "Invalid choice. Please try again." << endl;
        pause();
        displayMainMenu();
    }
}

void Ui::displayLoginMenu() {
    clearScreen();
    cout << "Login Menu" << endl;
    cout << "1. Admin Login" << endl;
    cout << "2. Customer Login" << endl;
    cout << "3. Worker Login" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "Please select an option: ";
    string choice;
    cin >> choice;
    clearScreen();
    if (choice == "1") {
        System::getInstance()->setUserType(UserType::ADMIN);
        string account, password;
        cout << "Enter Admin Account: ";
        cin >> account;
        cout << "Enter Password: ";
        cin >> password;
        if(System::getInstance()->login(account, password)){
            displayAdminMenu();
        } else {
            cout << "Login failed. Please try again." << endl;
            pause();
            displayLoginMenu();
        }
    } else if (choice == "2") {
        System::getInstance()->setUserType(UserType::CUSTOMER);
        string account, password;
        cout << "Enter Customer Account: ";
        cin >> account;
        cout << "Enter Password: ";
        cin >> password;
        if(System::getInstance()->login(account, password)){
            displayCustomerMenu();
        } else {
            cout << "Login failed. Please try again." << endl;
            pause();
            displayLoginMenu();
        }
    } else if (choice == "3") {
        System::getInstance()->setUserType(UserType::WORKER);
        string account, password;
        cout << "Enter Worker Account: ";
        cin >> account;
        cout << "Enter Password: ";
        cin >> password;
        if(System::getInstance()->login(account, password)){
            displayWorkerMenu();
        } else {
            cout << "Login failed. Please try again." << endl;
            pause();
            displayLoginMenu();
        }
    } else if (choice == "4") {
        displayMainMenu();
    } else {
        cout << "Invalid choice. Please try again." << endl;
        pause();
        displayLoginMenu();
    }
}

void Ui::displayRegisterMenu() {
    clearScreen();
    cout << "Register Menu" << endl;
    cout << "1. Register as Customer" << endl;
    cout << "2. Register as Worker" << endl;
    cout << "3. Back to Main Menu" << endl;
    cout << "Please select an option: ";
    string choice;
    cin >> choice;
    clearScreen();
    if (choice == "1") {
        string name, account, password, tel;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Account: ";
        cin >> account;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Telephone: ";
        cin >> tel;

    } else if (choice == "2") {
        string account, password;
        cout << "Enter Worker Account: ";
        cin >> account;
        cout << "Enter Password: ";
        cin >> password;
        if(System::getInstance()->registerWorker(account, password)){
            cout << "Worker registered successfully!" << endl;
            pause();
            displayMainMenu();
        } else {
            cout << "Registration failed. Please try again." << endl;
            pause();
            displayRegisterMenu();
        }
    } else if (choice == "3") {
        displayMainMenu();
    } else {
        cout << "Invalid choice. Please try again." << endl;
        pause();
        displayRegisterMenu();
    }
}

void Ui::displayAdminMenu(){
    clearScreen();
    cout << "Admin Menu" << endl;
}

void Ui::displayCustomerMenu(){
    clearScreen();
    cout << "Customer Menu" << endl;
}
void Ui::displayWorkerMenu(){
    clearScreen();
    cout << "Worker Menu" << endl;
}
