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
#ifdef DEBUG
    System::getInstance()->adminManager.viewAll();
#endif
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
    string choice;
    cin >> choice;
    if (choice == "1") {
        cout<< "Worker Management" << endl;
        
    }
    else if (choice == "2") {
        cout<< "Customer Management" << endl;

    } else if (choice == "3") {
        cout<< "Package Management" << endl;

    } else if (choice == "4") {
        cout<< "Exit" << endl;
        System::getInstance()->logout();
        displayMainMenu();
    } else {
        cout << "Invalid choice. Please try again." << endl;
        pause();
        displayAdminMenu();
    }
}

void Ui::displayCustomerMenu(){
    clearScreen();
    cout << "Customer Menu" << endl;
    string choice;
    cin >> choice;
    if (choice == "1") {
        cout<< "view contained packages" << endl;

    }
    else if (choice == "2") {
        cout<< "pick up package" << endl;

    }
    else if (choice == "3") {
        cout<< "Proxy pick up" << endl;

    }
    else if (choice == "4") {
        cout<< "Send package" << endl;

    } else if (choice == "5") {
        cout<< "View my sent packages" << endl;

    } else if (choice == "0") {
        System::getInstance()->logout();
        displayMainMenu();
    } else {
        cout << "Invalid choice. Please try again." << endl;
        pause();
        displayCustomerMenu();
    }
}

void Ui::displayWorkerMenu(){
    clearScreen();
    cout << "Worker Menu" << endl;
    string choice;
    cin >> choice;
    if (choice == "1") {
        cout<< "Receive package" << endl;

    }
    else if (choice == "2") {
        cout<< "Store package" << endl;

    }
    else if (choice == "3") {
        cout<< "Search package" << endl;

    }
    else if (choice == "4") {
        cout<< "Check remaining space" << endl;

    }
    else if (choice == "5") {
        cout<< "Send package" << endl;

    } else if (choice == "6") {
        System::getInstance()->logout();
        displayMainMenu();
    } else {
        cout << "Invalid choice. Please try again." << endl;
        pause();
        displayWorkerMenu();
    }
}

void Ui::displayWorkerManagementMenu() {
    clearScreen();
    cout << "Worker Management Menu" << endl;
    cout << "1. Add Worker" << endl;
    cout << "2. Remove Worker" << endl;
    cout << "3. View All Workers" << endl;
    cout << "4. Find Worker" << endl;
    cout << "5. Back to Admin Menu" << endl;
    cout << "Please select an option: ";
    
    string choice;
    cin >> choice;
    
    if (choice == "1") {
        string account, password;
        cout << "Enter Worker Account: ";
        cin >> account;
        cout << "Enter Password: ";
        cin >> password;
        Worker newWorker(account, password, System::getInstance()->workerManager.getNextId());
        System::getInstance()->workerManager.addData(make_shared<Worker>(newWorker));
    } else if (choice == "2") {
        int id;
        cout << "Enter Worker ID to remove: ";
        cin >> id;
        System::getInstance()->workerManager.removeData(id);
        cout << "Worker removed successfully." << endl;
    } else if (choice == "3") {
        System::getInstance()->workerManager.viewAll();
        pause();
        displayWorkerManagementMenu();
    } else if (choice == "4") {
        int id;
        cout << "Enter Worker ID to find: ";
        cin >> id;
        shared_ptr<Worker> worker = System::getInstance()->workerManager.getData(id);
        if (worker) {
            worker->display();
        } else {
            cout << "Worker not found." << endl;      
        }        
    } else if (choice == "5") {
        displayAdminMenu();
    } else {
        cout << "Invalid choice. Please try again." << endl;
        pause();
        displayWorkerManagementMenu();
    }
}

void Ui::displayCustomerManagementMenu() {
    clearScreen();
    cout << "Customer Management Menu" << endl;
    cout << "1. Add Customer" << endl;
    cout << "2. Remove Customer" << endl;
    cout << "3. View All Customers" << endl;
    cout << "4. Find Customer" << endl;
    cout << "5. Back to Admin Menu" << endl;
    cout << "Please select an option: ";
    
    string choice;
    cin >> choice;
    
    if (choice == "1") {
        // Add customer logic
    } else if (choice == "2") {
        // Remove customer logic
    } else if (choice == "3") {
        // View all customers logic
    } else if (choice == "4") {
        // Find customer logic
    } else if (choice == "5") {
        displayAdminMenu();
    } else {
        cout << "Invalid choice. Please try again." << endl;
        pause();
        displayCustomerManagementMenu();
    }
}

void Ui::displayPackageManagementMenu() {
    clearScreen();
    cout << "Package Management Menu" << endl;
    cout << "1. Add Contained Package" << endl;
    cout << "2. Remove Contained Package" << endl;
    cout << "3. View All Contained Packages" << endl;
    cout << "4. Find Contained Package" << endl;
    cout << "5. Back to Admin Menu" << endl;
    cout << "Please select an option: ";
    
    string choice;
    cin >> choice;
    
    if (choice == "1") {
        // Add package logic
    } else if (choice == "2") {
        // Remove package logic
    } else if (choice == "3") {
        // View all packages logic
    } else if (choice == "4") {
        // Find package logic
    } else if (choice == "5") {
        displayAdminMenu();
    } else {
        cout << "Invalid choice. Please try again." << endl;
        pause();
        displayPackageManagementMenu();
    }
}