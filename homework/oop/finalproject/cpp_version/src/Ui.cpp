#include <iostream>
#include "../include/Ui.h"
#include "../include/System.h"

using namespace std;

#ifdef _WIN32
    #define CLEAR "cls"
#elif __linux__
    #define CLEAR "clear"
#elif __APPLE__
    
#else
    
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
        exit(0);
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
        if(System::getInstance()->registerCustomer(name, account, password, tel)){
            cout << "Customer registered successfully!" << endl;
            pause();
            displayMainMenu();
        } else {
            cout << "Registration failed. Please try again." << endl;
            pause();
            displayRegisterMenu();
        }

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
    cout<< "1. Worker Management" << endl;
    cout<< "2. Customer Management" << endl;
    cout<< "3. Package Management" << endl;
    cout<< "4. Exit" << endl;
    string choice;
    cin >> choice;
    if (choice == "1") {
        cout<< "Worker Management" << endl;
        displayWorkerManagementMenu();
    }
    else if (choice == "2") {
        cout<< "Customer Management" << endl;
        displayCustomerManagementMenu();
    } else if (choice == "3") {
        cout<< "Package Management" << endl;
        displayPackageManagementMenu();
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
    cout << "1. View Contained Packages" << endl;
    cout << "2. Pick Up Package" << endl;
    cout << "3. Send Package" << endl;
    cout << "4. Logout" << endl;
    cout << "Please select an option: ";
    string choice;
    cin >> choice;
    if (choice == "1") {
        cout<< "view contained packages" << endl;
        Customer* curCustomer = dynamic_cast<Customer*>(System::getInstance()->getCurrentUser().get());
        curCustomer->DisplayContainedPackages();
        pause();
        displayCustomerMenu();
    }
    else if (choice == "2") {
        cout<< "pick up package" << endl;
        int id;
        cout << "Enter Package ID to pick up: ";
        cin >> id;
        Customer* curCustomer = dynamic_cast<Customer*>(System::getInstance()->getCurrentUser().get());
        curCustomer->PickupPackage(id);
        System::getInstance()->containedPackageManager.removeData(id);
        pause();
        displayCustomerMenu();
    }
    else if (choice == "3") {
        cout<< "Send package" << endl;
        int id;
        cout<< "Enter Package ID to send: ";
        cin >> id;
        Customer* curCustomer = dynamic_cast<Customer*>(System::getInstance()->getCurrentUser().get());
        curCustomer->SendPackage(id);
        System::getInstance()->containedPackageManager.removeData(id);
        cout << "Package with ID " << id << " sent successfully." << endl;
        pause();
        displayCustomerMenu();

    } else if (choice == "4") {
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
    cout << "1. Store Package" << endl;
    cout << "2. Search Package" << endl;
    cout << "3. View Incoming Package" << endl;
    cout << "4. Logout" << endl;
    string choice;
    cin >> choice;
    if (choice == "1") {
        cout<< "Store package" << endl;
        cout<< "Enter Package ID to store: ";
        int id;
        cin >> id;
        shared_ptr<ContainedPackage> package = System::getInstance()->incomingPackageManager.getData(id);
        if (package) {
            System::getInstance()->containedPackageManager.addData(package);
            System::getInstance()->incomingPackageManager.removeData(id);
            cout << "Package with ID " << id << " stored successfully." << endl;
        } else {
            cout << "Package with ID " << id << " not found." << endl;
        }
        pause();
        displayWorkerMenu();
    }
    else if (choice == "2") {
        cout<< "Search package" << endl;
        int id;
        cout << "Enter Package ID to search: ";
        cin >> id;
        System::getInstance()->incomingPackageManager.getData(id)->display();
        pause();
        displayWorkerMenu();
    }

    else if (choice == "3") {
        cout<< "View Incoming package" << endl;
        System::getInstance()->incomingPackageManager.viewAll();
        pause();
        displayWorkerMenu();

    } else if (choice == "4") {
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
        pause();
        displayWorkerManagementMenu();
    } else if (choice == "2") {
        int id;
        cout << "Enter Worker ID to remove: ";
        cin >> id;
        System::getInstance()->workerManager.removeData(id);
        cout << "Worker removed successfully." << endl;
        pause();
        displayWorkerManagementMenu();
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
        pause();
        displayWorkerManagementMenu();
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
        string name, account, password, tel;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Account: ";
        cin >> account;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Telephone: ";
        cin >> tel;
        
        Customer newCustomer(name, account, password, System::getInstance()->customerManager.getNextId(), 0, 0, tel);
        System::getInstance()->customerManager.addData(make_shared<Customer>(newCustomer));
        cout << "Customer added successfully." << endl;
        pause();
        displayCustomerManagementMenu();
    } else if (choice == "2") {
        // Remove customer logic
        int id;
        cout<< "Enter Customer ID to remove: ";
        cin >> id;
        System::getInstance()->customerManager.removeData(id);
        pause();
        displayCustomerManagementMenu();
    } else if (choice == "3") {
        // View all customers logic
        System::getInstance()->customerManager.viewAll();
        pause();
        displayCustomerManagementMenu();
    } else if (choice == "4") {
        // Find customer logic
        int id;
        cout << "Enter Customer ID to find: ";
        cin >> id;
        shared_ptr<Customer> customer = System::getInstance()->customerManager.getData(id);
        if (customer) {
            customer->display();
        } else {
            cout << "Customer not found." << endl;
        }
        pause();
        displayCustomerManagementMenu();
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
        string containerName, name, tel, pickupCode, company;
        float weight, volume;
        int inAddress, outAddress;
        int id = System::getInstance()->containedPackageManager.getNextId();
        time_t timestamp = time(nullptr);
        cout << "Enter Container Name: ";
        cin >> containerName;
        cout << "Enter Package Name: ";
        cin >> name;
        cout << "Enter Telephone: ";
        cin >> tel;
        cout << "Enter Pickup Code: ";
        cin >> pickupCode;
        cout << "Enter Company: ";
        cin >> company;
        cout << "Enter Weight: ";
        cin >> weight;
        cout << "Enter Volume: ";
        cin >> volume;
        cout << "Enter In Address: ";
        cin >> inAddress;
        cout << "Enter Out Address: ";
        cin >> outAddress;

        // Adjust the arguments below to match the actual constructor of ContainedPackage
        ContainedPackage newPackage(weight, volume, containerName, nullptr, name, tel, pickupCode, company, inAddress, outAddress, timestamp, id);
        System::getInstance()->containedPackageManager.addData(make_shared<ContainedPackage>(newPackage));
        cout << "Contained Package added successfully." << endl;
        pause();
        displayPackageManagementMenu();
    } else if (choice == "2") {
        // Remove package logic
        int id;
        cout << "Enter Contained Package ID to remove: ";
        cin >> id;
        System::getInstance()->containedPackageManager.removeData(id);
        cout << "Contained Package removed successfully." << endl;
        pause();
        displayPackageManagementMenu();
    } else if (choice == "3") {
        // View all packages logic
        System::getInstance()->containedPackageManager.viewAll();
        pause();
        displayPackageManagementMenu();
    } else if (choice == "4") {
        // Find package logic
        int id;
        cout << "Enter Contained Package ID to find: ";
        cin >> id;
        shared_ptr<ContainedPackage> package = System::getInstance()->containedPackageManager.getData(id);
        if (package) {
            package->display();
        } else {
            cout << "Contained Package not found." << endl;
        }
        pause();
        displayPackageManagementMenu();
    } else if (choice == "5") {
        displayAdminMenu();
    } else {
        cout << "Invalid choice. Please try again." << endl;
        pause();
        displayPackageManagementMenu();
    }
}