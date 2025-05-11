#pragma once
#include <list>
#include <unordered_map>
#include <memory>
#include "Package.h"

class PackageManager {
private:
    static PackageManager* instance;
    std::list<std::shared_ptr<Package>> incomingPackages;
    std::list<std::shared_ptr<Package>> storedPackages;
    std::unordered_map<std::string, std::list<std::shared_ptr<Package>>::iterator> packageMap;
    
    PackageManager() = default;

public:
    static PackageManager* getInstance();
    bool addPackage(std::shared_ptr<Package> package);
    bool removePackage(const std::string& id);
    std::shared_ptr<Package> findPackage(const std::string& id);
    bool assignLocker(std::shared_ptr<Package> package);
};
