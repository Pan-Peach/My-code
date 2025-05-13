#pragma once
#include <vector>
#include "Package.h"
#include "Manager.h"
using namespace std;

class Container:public Manager<ContainedPackage> {
private:
    int MaxCapacity;
    int CurrentCapacity;

public:
    Container()=default;
    Container(int maxCapacity) : MaxCapacity(maxCapacity), CurrentCapacity(0) {}
    ~Container() override = default;

    
};  