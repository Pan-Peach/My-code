#include "../include/ExpressManager.h"
#include <iostream>
#include <cstdlib>

#define _linux_
#define DEBUG

int main(){
    string adminFile = "../data/admin_data.txt";
    string customerFile = "../data/customer_data.txt";
    string workerFile = "../data/worker_data.txt";
    string containedPackageFile = "../data/contained_package_data.txt";
    System* system = System::getInstance();
    system->init(adminFile, customerFile, workerFile, containedPackageFile);
    return 0;
}