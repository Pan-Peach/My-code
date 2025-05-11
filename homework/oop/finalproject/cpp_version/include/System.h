#pragma once
#include <memory>
#include <vector>
#include "User.h"
#include "Package.h"

using namespace std;

class System {
private:
    static System* instance;
    vector<shared_ptr<User>> users;
    vector<shared_ptr<Package>> packages;

    System() = default;

public:
    static System* getInstance();
    
    bool login(const string& account, const string& password);
    void logout();
    bool registerUser(const string& name, const string& account, 
                     const string& password, const string& tel);
                     
    void addPackage(shared_ptr<Package> package);
    void removePackage(const string& id);
    shared_ptr<Package> findPackage(const string& id);
};
