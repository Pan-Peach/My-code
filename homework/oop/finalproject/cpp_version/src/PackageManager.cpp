#include "../include/PackageManager.h"
#include "../include/Package.h"

void ContainedPackageManager::ContainedPackages(CustomerManager& customerManager) {
    for(auto& package:dataList){
        int id = package->getOwnerId();
        shared_ptr<Customer> Ownerptr = customerManager.dataMap[id];
        if(Ownerptr){
            Ownerptr->containedPackage.push_back(package);
        }
        else{
            cout << "Error: Owner not found for package with ID: " << id << endl;
        }
    }

}
