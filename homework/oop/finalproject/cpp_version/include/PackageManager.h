#pragma once
#include <list>
#include <unordered_map>
#include <memory>
#include "Package.h"
#include "Manager.h"
#include "CustomerManager.h"
using namespace std;


class ContainedPackageManager : public Manager<ContainedPackage> {

public:
    void ContainedPackages(CustomerManager& customerManager);
};