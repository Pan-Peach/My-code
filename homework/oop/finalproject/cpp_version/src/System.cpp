#include "../include/System.h"
#include <cstdlib>

#ifdef _WIN32
    // Windows 平台代码
#elif __linux__
    // Linux 平台代码
#elif __APPLE__
    // macOS 平台代码
#else
    // 其他平台
#endif

System::System(){
    std::atexit([]() {
        System::getInstance()->exitSys();
    });
    ui = new Ui();
}

System* System::instance = nullptr;
System* System::getInstance() {
    if (instance == nullptr) {
        instance = new System();
    }
    return instance;
}

void System::init(const string& adminFile, const string& customerFile, const string& workerFile, const string& containedPackageFile) {
    adminManager.setFilename(adminFile);
    customerManager.setFilename(customerFile);
    workerManager.setFilename(workerFile);
    containedPackageManager.setFilename(containedPackageFile);

    adminManager.loadData();
    customerManager.loadData();
    workerManager.loadData();
    containedPackageManager.loadData();

    assignOwnerId();
    ui->clearScreen();
    inited = true;
    ui->displayMainMenu();
}

void System::exitSys(){
    if(!inited) {
        cout << "System not initialized. Exiting..." << endl;
        exit(0);
    }
    adminManager.saveData();
    customerManager.saveData();
    workerManager.saveData();
    containedPackageManager.saveData();
    cout << "Exiting the system. Goodbye!" << endl;
    delete instance;
    exit(0);
}

bool System::login(const string& account, const string& password) {
    if(currentUserType == UserType::ADMIN){
        if(adminManager.findAccount(account)){
            currentUser = adminManager.cmpPassword(account, password);
            if(currentUser){                
                cout << "Admin login successful!" << endl;
                return true;
            }
            else{
                cout << "Invalid password!" << endl;
                return false;
            }
        }
        else{
            cout << "Account not found!" << endl;
            return false;
        }
    }
    else if(currentUserType == UserType::CUSTOMER){
        if(customerManager.findAccount(account)){
            currentUser = customerManager.cmpPassword(account, password);
            if(currentUser){
                cout << "Customer login successful!" << endl;
                return true;
            }
            else{
                cout << "Invalid password!" << endl;
                return false;
            }
        }
        else{
            cout << "Account not found!" << endl;
            return false;
        }
    }
    else if(currentUserType == UserType::WORKER){
        if(workerManager.findAccount(account)){
            currentUser = workerManager.cmpPassword(account, password);
            if(currentUser){
                cout << "Worker login successful!" << endl;
                return true;
            }
            else{
                cout << "Invalid password!" << endl;
                return false;
            }
        }
        else{
            cout << "Account not found!" << endl;
            return false;
        }
    }
    else{
        cout << "Invalid user type!" << endl;
        return false;
    }
    return false;
}

void System::logout() {
    cout << "Logging out..." << endl;
    currentUserType = UserType::CUSTOMER; // Reset to default
    ui->displayMainMenu();
}
bool System::registerCustomer(const string& name, const string& account, const string& password, const string& tel) {
    if (customerManager.findAccount(account)) {
        return false;
    }
    else{
        shared_ptr<Customer> newCustomer = make_shared<Customer>(name, account, password, customerManager.getNextId(), 0, 0, tel);
        customerManager.addData(newCustomer);
        return true;
    }
}
bool System::registerWorker(const string& account, const string& password) {
    if (workerManager.findAccount(account)) {
        return false;
    }
    else{
        shared_ptr<Worker> newWorker = make_shared<Worker>(account, password, workerManager.getNextId());
        workerManager.addData(newWorker);
        return true;
    }
}

void System::assignOwnerId() {
    for (const auto& package : containedPackageManager.getDataList()) {
        int ownerId = package->getOwnerId();
        shared_ptr<Customer> owner = customerManager.getData(ownerId);
        if (owner) {
            owner->addContainedPackage(package);
        } else {
            cout << "Error: Owner with ID " << ownerId << " not found for package with ID " << package->getId() << "." << endl;
        }
    }
}