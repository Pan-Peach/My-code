#pragma once
#include <memory>
#include <vector>
#include <cstdlib>
#include "User.h"
#include "Package.h"
#include "Ui.h"
#include "PackageManager.h"
#include "AdminManager.h"
#include "CustomerManager.h"
#include "WorkerManager.h"


using namespace std;


enum class UserType {
    ADMIN,
    CUSTOMER,
    WORKER
};

class System {
private:
    static System* instance;

    System();

    Ui *ui ;
    bool inited = false;
    enum UserType currentUserType;  

public:
    AdminManager adminManager;
    CustomerManager customerManager;
    WorkerManager workerManager;
    static System* getInstance();
    
    void init(const string& adminFile, const string& customerFile, const string& workerFile);

    void setUserType(UserType type) {
        currentUserType = type;
    }

    bool login(const string& account, const string& password);
    void logout();
    void exitSys();
    bool registerCustomer(const string& name, const string& account, const string& password, const string& tel);
    bool registerWorker(const string& account, const string& password);
    bool registerAdmin(const string& account, const string& password);
                     
    
};
